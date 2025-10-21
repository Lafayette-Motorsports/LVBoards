# MotorsportsLVBoards

LV Board repository for Motorsports created 09.02.2025  

## BE SURE TO COMMIT & PUSH ALL CHANGES WHEN FINISHED TO KEEP THINGS UPDATED  

## Modulation
LV Boards are now 'modulated' - this means that each board is designed to serve a single purpose so that individual circuits/functions can be easily replaced  
    This means that wires need to be obviosuly labeled with their purpose and output params/types to keep things 'open source' enough that it can be easily updated -- keep documentation (wiring diagram, code comments, standalone documentation) updated, descriptive, and accurate  

## If this is your first time
To use this and work on the board (non cmd because if you don't know this you don't need to be trying to do it on the console):  
    - make a github account   
        - you can do this with your school email or your personal but if you plan on making changes, make your screen name traceable (eg. we want to be able to know who's doing stuff)  
    - download github for desktop (https://desktop.github.com/download/) and sign in  
    - 'follow' this repository to add it to your account  
    - click current repository (top left) --> add --> clone repository --> pull origin  
    - find your file path (repository --> show in explorer) and open whatever you want  
    - if you make changes, YOU NEED TO MANUALLY UPDATE THE REPOSITORY, ALL CHANGES MADE ARE LOCAL UNTIL THIS IS DONE  
        - go back to your github app and open the repository (its probably still open), add a summary and commit your changes, push to origin  
        - MAKE YOUR SUMMARY SOMEWHAT DETAILED, YOU DON'T NEED A PARAGRAPH BUT THIS IS A REALLY GOOD PLACE TO PUT A CHANGE LOG SO WE CAN TRACK WHATS HAPPENING WHEN AND GET A SOMEWHAT DETAILED HISTORY  

## Component Cacheing
When adding parts, store them as project-specific rather than global. You will need to create your own library for the project, but you should really only need to do it once per KiCad project -- this will make sure that projects are actually portable. Some projects were built without this in mind so be weary when trying to modify/process files -- they might not have footprints/symbols for every part. If you can't figure out how to do this (or you think you added a symbol but it's not working, footprint not loading, etc.) google it or ask -- the whole point of the GitHub is portability so its kind of stupid to ignore this.

  
for repository admin (or other) questions - Sean McLoughlin mclougsm@lafayette.edu
