#!/usr/bin/env python 
import argparse, sys, re

parser = argparse.ArgumentParser(description='')
parser.add_argument('-t', dest='template', help='Template file')
parser.add_argument('-o', dest='output', help='Output file')
parser.add_argument('-c', dest='content', help='Generated content to replace')
parser.add_argument('-r', dest='regex', help='Regular expression to match and replace')
parser.add_argument('-j', dest='join', help="How to join content lines", default='\n')

args = parser.parse_args()

content = None
if args.content:
    content = open(args.content.read())
else:
    content = sys.stdin.read()

save = []
# clean up content 
for line in content.split('\n'):
    if len(line.strip()) == 0:
        continue 

    m = re.match("^#[^\n]*$", line.strip(), re.MULTILINE)
    if not m:
        save.append(line.strip())

template = open(args.template).read()

template = template.replace(args.regex, args.join.join(save))

open(args.output, 'w').write(template)


