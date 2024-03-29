import os
import subprocess
import curses
import time

# ADD this line to your .bashrc:
# alias sjobs='python3 ~/PP_Legenden/sjobs.py'

# TODO pass folder as arguments

def get_shell_scripts():
    """Get a list of all the shell scripts in the current directory"""
    files = os.listdir('.')
    shell_scripts = []
    for file in files:
        if file.endswith('.sh'):
            shell_scripts.append(file)
    return shell_scripts

def get_job_ids():
    """Get a list of all the job IDs from the squeue command"""
    output = os.popen('squeue -u $USER -h -o %i').read()
    job_ids = output.strip().split('\n')
    return job_ids

def main(stdscr):
    time.sleep(1/10)
    curses.curs_set(0)
    curses.noecho()
    stdscr.nodelay(True)
    curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_GREEN)

    selected_list_index = 1

    selected_file_index = 0
    selected_jobs_index = 0

    makemsg = 100

    while True:
        rows, cols = stdscr.getmaxyx()
        stdscr.clear()

        shell_scripts = get_shell_scripts()
        if selected_file_index > len(shell_scripts):
            selected_file_index = len(shell_scripts) -1

        job_ids = get_job_ids()
        if selected_jobs_index > len(job_ids):
            selected_jobs_index = len(job_ids) - 1

        if makemsg < 30:
            stdscr.addstr(rows -2, 0, 'Executed make command')
            makemsg += 1

        stdscr.addstr(0, 0, os.popen('squeue -u $USER').read())

        stdscr.addstr(rows -1, 0, 'Switch lists with right/left arrow, sbatch job with s, scancel with c, quit with q')

        if len(shell_scripts) > 0:
            stdscr.addstr(5, 11, f'Found shell scripts: {len(shell_scripts)}')
        else:
            stdscr.addstr(5, 11, 'No shell scripts in this folder')

        for i, script in enumerate(shell_scripts):
            if i == selected_file_index and selected_list_index == 1:
                stdscr.addstr(i + 6, 11, f'> {script}', curses.color_pair(1))
            else:
                stdscr.addstr(i + 6, 11, f'  {script}')

        for i, job in enumerate(job_ids):
            if i == selected_jobs_index and selected_list_index == 0:
                stdscr.addstr(i + 1, 11, f'> {job}', curses.color_pair(1))
            else:
                stdscr.addstr(i + 1, 11, f'  {job}')

        key = stdscr.getch()
        curses.flushinp()

        if key == curses.KEY_UP:
            selected_file_index = max(selected_file_index - 1, 0)
            selected_jobs_index = max(selected_jobs_index - 1, 0)
        elif key == curses.KEY_DOWN:
            selected_file_index = min(selected_file_index + 1, len(shell_scripts) - 1)
            selected_jobs_index = min(selected_jobs_index + 1, len(job_ids) - 1)
        elif key == curses.KEY_LEFT and selected_list_index > 0:
            selected_list_index -= 1
        elif key == curses.KEY_RIGHT and selected_list_index < 1:
            selected_list_index += 1
        elif key == ord('s') or key == curses.KEY_ENTER  or key == 10 or key == 13:
            os.system('make')
            makemsg = 0
            selected_file = shell_scripts[selected_file_index]
            os.system(f'sbatch {selected_file}')
        elif key == ord('c'):
            os.system(f'scancel {job_ids[selected_jobs_index]}')
        elif key == ord('q'):
            os.system('make clean')
            break

if __name__ == '__main__':
    curses.wrapper(main)
