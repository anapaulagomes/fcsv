import fcsv


data = [{'paula': 'aaa1', 'b': 'bbbb'}, {'a2': 'aaa2'}, {'a': 'aaa3'}]

# def create(data):  # lista de dicionarios
#     header = data[0].keys()
#     values = [row.values() for row in data]

#     return header, values

# header, values = create(data)
# fcsv.create(header, values)

fcsv.create(data)