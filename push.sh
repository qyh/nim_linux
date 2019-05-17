#!/bin/bash
account="xx"
passwd="xx"
expect <<!
    spawn git push origin master 
    expect {
		"Password *" {send "$passwd\n"; exp_continue}
		"Username *" {send "$account\n"; exp_continue}
    }
!
