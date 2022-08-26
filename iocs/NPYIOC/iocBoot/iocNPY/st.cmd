errlogInit(20000)

< envPaths
#epicsThreadSleep(20)
dbLoadDatabase("$(TOP)/dbd/NPYApp.dbd")
NPYApp_registerRecordDeviceDriver(pdbbase) 


iocshLoad("ADNPYReader.iocsh", "PREFIX=NPY1:, PORT=NPY1")

set_requestfile_path("$(ADNPY)/ADNPYReaderApp/Db")

##########
iocInit()
##########

# save things every thirty seconds
create_monitor_set("auto_settings.req", 30, "P=NPY1:")
