import argparse
import os
import csv
from distutils import dir_util


def main(dir, max_size, times, sbatch):
    print '\n@@ Got dir: '+dir   
    print '\n@@ Got times: '+str(times)
    dir = os.path.abspath(dir)

    results = {}

    with open('reults.csv', 'w') as results_file:
        fieldnames = ['n', 'test_name', 'mat_size', 'serial', 'p4a', 'rose', 'correct']
        writer = csv.DictWriter(results_file, fieldnames=fieldnames)
        writer.writeheader()

        for n in range(1000, max_size+1, 1000):
            results[n] = {}
            for i in range(0,times):
                results[n][i] = {}
                for ap in ['','_p4a','_rose']:
                    filename = os.path.join(dir,'run_tests'+ap+'_'+str(n)+'_'+str(i)+'.csv')
                    print filename
                    if ap == '':
                        ap = 'serial'
                    with open(filename, 'rb') as csvfile:
                        reader = csv.DictReader(csvfile)
                        for row in reader:
                            results[n][i][ap][row['test_name']] = row['time']
                            results[n][i][row['test_name']]['corret'] += row['correct']
                            print results




                # serial_res = os.path.join(dir,'run_tests_'+str(n)+'_'+str(i)+'.csv')
                # p4a_res = os.path.join(dir,'run_tests_p4a_'+str(n)+'_'+str(i)+'.csv')
                # rose_res = os.path.join(dir,'run_tests_rose_'+str(n)+'_'+str(i)+'.csv')
                
                # serial_res_file=  open(serial_res, 'rb')
                # p4a_res_file = open(p4a_res, 'rb')
                # rose_res_file = open(rose_res, 'rb')

                # serial_res_reader = csv.DictReader(serial_res_file)
                # p4a_res_reader = csv.DictReader(p4a_res_file)
                # rose_res_reader = csv.DictReader(rose_res_file)
                # print '@@@@ '+serial_res
                # for a in serial_res_reader:
                #     print a 
                # print '@@@@ '+p4a_res
                # for a in p4a_res_reader:
                #     print a
                # print '@@@@ '+rose_res
                # for a in rose_res_reader:
                #     print a
                # for a,b,c in zip(serial_res_reader, p4a_res_reader, rose_res_reader):
                #     print [a,b,c]





    #             for ap in ['','_p4a','_rose']:
    #                 filename = os.path.join(dir,'run_tests'+ap+'_'+str(n)+'_'+str(i)+'.csv')
    #                 print filename
    #                 row = {'n': n, 'test_name':, 'mat_size':, 'serial', 'p4a', 'rose', 'correct'}
    #                 with open(filename, 'rb') as csvfile:
    #                     reader = csv.DictReader(csvfile)
    #                     for row1 row2 row3 in reader:
    #                         print row


    #        writer.writerow({'first_name': 'Baked', 'last_name': 'Beans'})
    # writer.writerow({'first_name': 'Lovely', 'last_name': 'Spam'})
    # writer.writerow({'first_name': 'Wonderful', 'last_name': 'Spam'})
    for root, dirs, files in os.walk(dir):
        for name in files:
            if os.path.splitext(name)[1] == '.csv':
                print name




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