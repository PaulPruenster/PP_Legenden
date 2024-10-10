import os
import curses
import time

# ADD this line to your .bashrc:
# alias sjobs='python3 ~/PP_Legenden/sjobs.py'

class Data:
    def __init__(self, stdscr, selected_file_index, selected_jobs_index, selected_list_index) -> None:
        self.shell_scripts = None
        self.running = True

        self.stdscr = stdscr
        self.selected_file_index = selected_file_index
        self.selected_jobs_index = selected_jobs_index
        self.selected_list_index = selected_list_index

def get_shell_scripts():
    files = os.listdir('.')
    shell_scripts = []
    for file in files:
        if file.endswith('.sh'):
            shell_scripts.append(file)
    return shell_scripts

def get_job_ids():
    output = os.popen('squeue -u $USER -h -o %i').read()
    job_ids = output.strip().split('\n')
    return job_ids

def render_ui(data: Data):
    data.stdscr.erase()
    rows, cols = data.stdscr.getmaxyx()

    if cols <= 20 or rows < 1:
        return

    if cols <= 110 or rows <= 15:
        x = (cols // 2) - 10
        y = (rows // 2) - 1
        data.stdscr.addstr(y, x, "Window is to small!")
        return


    data.stdscr.addstr(0, 0, os.popen('squeue -u $USER -o "%.9i %.9P %.23j %.2t %.8M %.6D %.8Q %.12l %.9m %.4C %.16S %r"').read())
    data.stdscr.addstr(rows -1, 2, 'Switch lists with right/left arrow, sbatch with s, scancel with c, quit with q')

    if len(data.shell_scripts) > 0:
        data.stdscr.addstr(rows - len(data.shell_scripts) - 3, 3, f'Found shell scripts: {len(data.shell_scripts)}')
    else:
        data.stdscr.addstr(rows - len(data.shell_scripts) - 3, 3, 'No shell scripts in this folder')

    for i, script in enumerate(data.shell_scripts):
        if i == data.selected_file_index and data.selected_list_index == 1:
            data.stdscr.addstr(i + rows - len(data.shell_scripts) - 2, 3, f'> {script}', curses.color_pair(1))
        else:
            data.stdscr.addstr(i + rows - len(data.shell_scripts) - 2, 3, f'  {script}')

    for i, job in enumerate(data.job_ids):
        if i == data.selected_jobs_index and data.selected_list_index == 0:
            data.stdscr.addstr(i + 1, 0, f'> {job}', curses.color_pair(1))
        else:
            data.stdscr.addstr(i + 1, 0, f'  {job}')
               
def handle_keys(data: Data):
    key = data.stdscr.getch()
    curses.flushinp()
    
    if key == curses.KEY_UP:
        data.selected_file_index = max(data.selected_file_index - 1, 0)
        data.selected_jobs_index = max(data.selected_jobs_index - 1, 0)
    elif key == curses.KEY_DOWN:
        data.selected_file_index = min(data.selected_file_index + 1, len(data.shell_scripts) - 1)
        data.selected_jobs_index = min(data.selected_jobs_index + 1, len(data.job_ids) - 1)
        
    elif key == curses.KEY_LEFT and data.selected_list_index > 0:
        data.selected_list_index -= 1
    elif key == curses.KEY_RIGHT and data.selected_list_index < 1:
        data.selected_list_index += 1
        
    elif key == ord('s') or key == curses.KEY_ENTER  or key == 10 or key == 13:
        status = os.system(f'sbatch {data.shell_scripts[data.selected_file_index]}')
        data.stdscr.clear()
        if status != 0:
            data.running= False
        
    elif key == ord('c'):
        os.system(f'scancel {data.job_ids[data.selected_jobs_index]}')
    elif key == ord('q'):
        data.running = False
    
def update_data(data):
    data.shell_scripts = get_shell_scripts()
    if data.selected_file_index > len(data.shell_scripts):
        data.selected_file_index = len(data.shell_scripts) -1

    data.job_ids = get_job_ids()
    if data.selected_jobs_index > len(data.job_ids):
        data.selected_jobs_index = len(data.job_ids) - 1

def main(stdscr: curses.window):
    stdscr.nodelay(True)
    curses.curs_set(0)
    curses.noecho()
    curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_GREEN)
    
    data = Data(
        stdscr, 
        selected_file_index=0, 
        selected_jobs_index=0, 
        selected_list_index=1
    )
    while data.running:
        time.sleep(1/30)
        
        update_data(data)

        render_ui(data)

        handle_keys(data)

if __name__ == '__main__':
    curses.wrapper(main)
