import fcsv


big_field = 'z' * 200000

data = [
    {'a': 'aaa1', 'b': 'bbbb'},
    {'a': 'aaa2', 'b': 'yyyewr'},
    {'a': 'aaa3', 'b': big_field},
]

print(fcsv.create(data))