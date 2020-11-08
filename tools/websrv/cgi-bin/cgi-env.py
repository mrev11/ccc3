#! /usr/bin/env python
# _*_  coding: utf-8 _*_

import os

print("Content-Type: text/plain\n")

env=os.environ
for name in env.keys():
    print(name+"="+env[name])


