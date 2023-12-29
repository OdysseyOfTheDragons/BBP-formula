# Server

The server works with files, for a few reasons:
* fast
* human-readable
* the file's title can be used to store data (type _hex_ or _dec_, starting point, number of digits...)

The server stores data in a status.json:
* the actual digit to calculate
* all the files to the already calculated digits, with the start, number, and the IP which calculated the digits
