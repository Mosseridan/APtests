import argparse
import os
import subprocess
import distutils
import time
from distutils import dir_util

def mkdir_if_none_exits(path):
    try:
        os.makedirs(path)
    except OSError as e:
        if e.errno != os.errno.EEXIST:
            raise

def make_batch_file(test_name, test_dir):
    print '\n@@ Making batch script'
    batch_file_path = os.path.join(test_dir, 'batch_job.sh')
    batch_file = open(batch_file_path,'w')
    batch_file.write(
        '#!/bin/bash\n'
        + '#SBATCH --exclusive\n'
        + '$@\n'
    ) 
    batch_file.close()
    return batch_file_path

def run_test(test, dest_dir, max_size, times, sbatch):
    test_name = os.path.splitext(os.path.basename(test))[0]
    if(sbatch):
        batch_file = make_batch_file(test_name, dest_dir)     
        for n in range(1000, max_size+1, 1000):
            for i in range(0,times):
                print '@ '+str(n)+' : '+str(i)
                sub_proc = subprocess.Popen(['sbach', '-o', test_name+'_'+str(n)+'_'+str(i), batch_file, test, str(n)], cwd=dest_dir)
                sub_proc.wait()
    else:
        for n in range(1000, max_size+1, 1000):
            for i in range(0,times):
                print '@ '+str(n)+' : '+str(i)
                sub_proc = subprocess.Popen([test, str(n), '|', 'tee',test_name+'_'+str(n)+'_'+str(i)], cwd=dest_dir)
                sub_proc.wait()



def main(dir, max_size, times, sbatch):
    print '\n@@ Got dir: '+dir   
    print '\n@@ Got times: '+str(times)

    dir = os.path.abspath(dir)
    dir_name = os.path.basename(dir)
    timestr = time.strftime("%y%m%d%H%M%S")
    dest_dir = os.path.abspath(os.path.join('results',dir_name+'_results_'+timestr))
    mkdir_if_none_exits(dest_dir) 
    print '\n@@ destination directory: '+dest_dir

    for root, dirs, files in os.walk(dir):
        for name in files:
            if os.path.splitext(name)[1] == '.out':
                test = os.path.join(root,name)
                print "@@ runing test: "+test
                run_test(test, dest_dir, max_size, times, sbatch)





if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Runs tests with varying input sizes.')
    parser.add_argument('-dir',
        dest='dir',
        help='Path to the directory containing the tests.')
    parser.add_argument('-n',
        type=int,
        dest='max_size',
        help='Maximum input size.')
    parser.add_argument('-t',
        type=int,
        dest='times',
        help='Number of times each test will be executed.')
    parser.add_argument('-sbatch',
        action='store_true',
        dest='sbatch',
        help='Run with sbatch.')
    args = parser.parse_args()

    main(args.dir, args.max_size,args.times, args.sbatch)

    print "\n@@ Done"