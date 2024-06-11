#!/bin/bash

set -e

file_name=$1
attr_name=$2

if [[ -z "$file_name" || -z "$attr_name" ]]; then
    echo "Usage: create_new_attr.sh <attr_name> <attr_type>"
    echo "Example: create_new_attr.sh my_attr MyAttr"
    exit 1
fi

# Check if we are in src/compiler/frontend/attrs/builtin
if [[ ! -f "create_new_attr.sh" ]]; then
    echo "Please run this script from src/compiler/frontend/attrs/builtin"
    exit 1
fi

output_file="$file_name.h"
if [[ -f "$output_file" ]]; then
    echo "File $output_file already exists"
    echo "Please delete it before running this script"
    exit 1
fi

echo "Creating new attribute $attr_name in $output_file"

# Add the attribute to the list of attributes
base_contents=$(cat empty.temp)

# Replace $file_name with the new attribute name
new_contents=$(echo "$base_contents" | sed "s/\$file_name/$file_name/g")
new_contents=$(echo "$new_contents" | sed "s/\$attr_name/$attr_name/g")

echo "$new_contents" > $output_file
