#!/usr/bin/env python 
import argparse, sys, re

parser = argparse.ArgumentParser(description='')
parser.add_argument('-t', dest='template', help='Template file')
parser.add_argument('-o', dest='output', help='Output file')
parser.add_argument('-c', dest='content', help='Generated content to replace')
parser.add_argument('-r', dest='regex', help='Regular expression to match and replace')

args = parser.parse_args()

content = None
if args.content:
    content = open(args.content.read())
else:
    content = sys.stdin.read()

save = []
# clean up content 
for line in content.split('\n'):
    m = re.match("^#[^\n]*$", line, re.MULTILINE)
    if not m:
        save.append(line)

template = open(args.template).read()

template = template.replace(args.regex, "\n".join(save))

open(args.output, 'w').write(template)


