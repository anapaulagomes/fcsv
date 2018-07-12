import fcsv
import time
import csv
import datetime
import os


def write_with_python(data):
    filename = 'filename-with-python.csv'
    with open(filename, 'w', newline="") as csvfile:
        fieldnames = data[0].keys()
        writer = csv.DictWriter(
            csvfile, fieldnames=fieldnames,
        )
        writer.writeheader()
        writer.writerows(data)
    return filename

def create_data(number_of_rows):
    big_field = 'z' * 200000
    big_data = [
        {'a': f'aaa{number}', 'b': big_field} for number in range(number_of_rows)
    ]
    return big_data

python_times = []
c_times = []
number_of_rows_list = [10, 100, 1000, 1000000]  # WARNING: 1000000 rows can occupy 200GB of disk

for number_of_rows in number_of_rows_list:
    start = time.time()
    write_with_python(create_data(number_of_rows))
    elapsed = datetime.timedelta(seconds=time.time() - start)
    python_times.append(elapsed)
    os.remove('filename-with-python.csv')

    start = time.time()
    fcsv.create(create_data(number_of_rows))
    elapsed = datetime.timedelta(seconds=time.time() - start)
    c_times.append(elapsed)
    os.remove('filename.csv')

for python, c, rows in zip(python_times, c_times, number_of_rows_list):
    print(f'{rows} = {python} | {c}')
