#!/usr/bin/python3

if __name__ == '__main__':
    string = '今日は'
    for char in string:
        print(char)

    ch1 = '日'
    print(string.find(ch1))

    ch2 = 'じ'
    print(string.find(ch2))
