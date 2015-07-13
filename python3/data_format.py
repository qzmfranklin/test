#!/usr/local/bin/python3

import json
import sys


if __name__ == '__main__':
    session = {
            'timestamp' : '2015-07-02T12:23:12Z', # ISO-8601 datetime format
            'session' : [
                {
                    'action' : 'STS',
                    'locale' : 'en-US',
                    'keyboard' : {
                        'layout' : 'QWERTY',
                        'id' : 1,
                        'size' : [ 200, 160 ]
                        },
                    'textfield' : {
                        'type' : 0,
                        'action' : 1
                        },
                    'ac' : {
                        'on' : False
                        }
                    },
                {
                    'action' : 'P',
                    'coordinates' : [ 91.32, 342.21]
                    },
                {
                    'action' : 'P',
                    'coordinates' : [ 91.32, 342.21]
                    },
                {
                    'action' : 'P',
                    'coordinates' : [ 91.32, 342.21]
                    },
                {
                    'action' : 'SR', # space is SP
                    'corrected' : 'was'
                    },
                {
                    'action' : 'SD',
                    'corrected' : 'sad'
                    },
                {
                    'action' : 'ETS'
                    }
                ]
            }

    blob = {
            'platform' : {
                'version' : '6.0.0',
                'device' : 'SamsungS6',
                'os' : 'android21',
                'resolution' : [ 2048, 1680 ],
                },
            'engine' : {
                'version' : '1.60'
                },
            'sessions' : [
                session
                ]
            }

    json.dump(blob, sys.stdout, indent = 4, ensure_ascii = False)
