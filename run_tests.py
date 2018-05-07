import argparse
import os
import subprocess
import distutils
import time
from distutils import dir_util

def run_test(test, dest_dir, max_size, times):
    test_name = os.path.splitext(os.path.basename(test))[0]
    for i in range(0,times):
        print '@ ' + str(i)
        for n in
        sub_proc = subprocess.Popen([test, '> '+test_name+'_'+str(i)+'_results'], cwd=dest_dir)
        sub_proc.wait()


def main(dir, max_size, times):
    print '\n@@ Got dir: '+dir   
    print '\n@@ Got times: '+str(times)

    dir = os.path.abspath(dir)
    dir_name = os.path.basename(dir)
    timestr = time.strftime("%y%m%d%H%M%S")
    dest_dir = os.path.abspath(os.path.join('results',dir_name+'_results_'+timestr))
    os.mkdir(dest_dir)    
    print '\n@@ destination directory: '+dest_dir

    for root, dirs, files in os.walk(dir):
        for name in files:
            if os.path.splitext(name)[1] == '.out':
                test = os.path.join(root,name)
                print "@@ runing test: "+test
                run_test(test, dest_dir, max_size, times)





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
    args = parser.parse_args()

    main(args.dir, args.max_size,args.times)

    print "\n@@ Done"