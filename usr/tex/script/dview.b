#!/bin/bash
echo active >dview
evince $1
rm dview
