#!/bin/sh

cmd="${1}"
case ${cmd} in
    makeall)
        sh -c 'cd driver/binder && make'
        sh -c 'cd test && make'
        ;;
    clean)
        sh -c 'cd driver/binder && make clean'
        sh -c 'cd test && make clean'
        ;;
    insmod)
        sh -c 'sudo insmod driver/binder/binder_linux.ko'
        ;;
    rmmod)
        sh -c 'sudo rmmod binder_linux'
        ;;
   *)
      echo "`basename ${0}`:usage: [makeall] | [clean] | [insmod] | [rmmod]"
      exit 1
      ;;
esac