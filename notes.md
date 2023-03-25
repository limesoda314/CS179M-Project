## Notes 

C:\Users\lime\Documents\CS179M\CS179M-Project\Manifests\ShipCase1.txt

### inputs 
- inbound manifest 
- transfer list 
    - crane operators interpret this info and input it into the system 
- sign in 


### Generate log file
- sign in crane operators 
- automatically sign out previous crane operator 
- comments can not be deleted, only amended in later comments 
- must track all atomic moves 


### Animation 
- display current movement on screen
- loop untile operation finishes 


### Updated outbound manifest 
- deleted manually only after emailing 


## main screen options 
- login 
- import manifest
- load
    - ask for name of cargo
    - ask for mass 
    - we calculate where it should go in the ship 
- unload 
- balance 
    - given the manifest, we give the sequence of moves to rearrange the cargo so that it is balanced 
- make comment 
- done (mark done with atomic move)



## Scenario 1
- move shipping containers on and off ship based on crane operators interpretation of the transfer list 

## Scenario 2
- balance cargo on ship such that difference between right and left side is no more thatn 10% 


## manifest format 

[yy,xx], {00000}, NAN
[yy,xx], {02000}, Cat
[yy,xx], {00000}, Unused

NAN = can't place a block there 
cat = name of shipping container, can move container but can't move another container there 
Unused = space that isn't used, can move container there 
{02000} = mass of cargo container 

* when completing a move we should highlight the box we need to move as well as the square we want to move to 
* since the names are concatenated inside of the boxes, we should have the option where you see the full name of the box you're moving in specific area 
* use same format for updated manifest 
* don't need to keep original manifest 

## log file format 
title: logfile_yyyy.txt 

* should only be viewed/comments added 

content
Date: timestamp Action/comment 

Example log file 
```
June 1st 2023: 00:02 John Smith signs out
June 1st 2023: 00:02 Anil Patel signs in
June 1st 2023: 02:04 Manifest HMMAlgeciras.txt is opened, there are 12 containers on the ship
June 1st 2023: 04:23 “Walmart Bikes Moreno Valley South” is offloaded.
June 1st 2023: 04:55 I notice that the “Walmart Toasters Moreno Valley South” container has a large fresh-looking dent on the door. However, door was not breeched, so just sent a photo to head office and I am continuing with the cycle.  
June 1st 2023: 04:56 “Walmart Toasters Moreno Valley South” is offloaded.
June 1st 2023: 05:34 “Amazon Empty, Let John or Mike in packaging when arrives” is onloaded.
June 1st 2023: 06:02 Finished a Cycle. Manifest HMMAlgecirasOUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.
June 1st 2023: 07:11 Manifest HMMAFreiger.txt is opened, there are 34 containers on the ship
June 1st 2023: 07:43 “Apple Valley Machine parts, call 902-555-2322 if problem” is offloaded.
June 1st 2023: 07:47 I noticed that “Apple Valley Machine parts” is about 10% over its stated weight, may be due to the rain on top, no further action taken.
June 1st 2023: 07:59 Anil Patel signs out
June 1st 2023: 08:00 Sue Smith signs in
June 1st 2023: 08:12 “Apple Valley Tires, call 902-555-2322 if problem” is offloaded.
::  
June 2nd 2023: 01:13 Finished a Cycle. Manifest HMMAFreigerOUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.
```



unload: 

1. PIE
2. PSA
3. ASG 
... 


load: 
container name: 
container mass (0 for empty): 

ALL ships fit within an 8x12 grid 