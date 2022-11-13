# ACE2005 preprocessing

This is a script to convert ACE2005 dataset from json data format to MLBiNet data
format.

## Usage

```shell
usage: convert2MLBinet.py [-h] [--data DATA] [--type TYPE] [--debug DEBUG]

optional arguments:
  -h, --help     show this help message and exit
  --data DATA    Path of converted ACE2005 English data in json format.
  --type TYPE    Type of data to be preprocessed. Available types: dev, test, train
  --debug DEBUG  Get more output info for debug purpose.
```

## Example

```shell
py convert2MLBinet.py --data ./ace-event/debug.json   --type dev --debug True
```

This take example dateset `./ace-event/debug.json` as input, save output to
`./output/debug.json.dev`

The samples are uploaded with this script.
