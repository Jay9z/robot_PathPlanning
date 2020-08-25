# robot_PathPlanning
path planning


# pre-requisites
## add c++11 arguments for 'run code' 
1. open settings.json from Code Runner's extension setting
2. add following configuration to .json file
   
   '''
    {
    "code-runner.runInTerminal": true,
    "C_Cpp.default.cppStandard": "c++11",
    "code-runner.executorMap": {
       "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -std=c++11 && $dir$fileNameWithoutExt"
    },
    "files.associations": {
    "typeinfo": "cpp"
    },
    "window.zoomLevel": 1, 
    }
    '''

# 