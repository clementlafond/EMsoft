
set(EXE_LINK_LIBRARIES "EMsoftLib")

if (Fortran_COMPILER_NAME MATCHES "gfortran.*")
  set(EXE_LINK_LIBRARIES ${EXE_LINK_LIBRARIES} gomp gcc_eh)
endif()

if (Fortran_COMPILER_NAME MATCHES "ifort.*")
  if(WIN32)
    add_definitions("/Qopenmp /Qdiag-disable:11082 /Qip")
  endif()
endif()

include_directories("${EMsoftHDFLib_BINARY_DIR}")


set(APP_DIR "${EMsoft_SOURCE_DIR}/Source/Utilities")
set(TMPLT_DIR "${EMsoft_SOURCE_DIR}/NamelistTemplates")
set(LIB_SEARCH_DIRS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


if(EMsoft_ENABLE_HDF5_SUPPORT)
  
      GetHDF5LinkLibraries(EMSOFT)
      set(EXE_LINK_LIBRARIES ${EXE_LINK_LIBRARIES} ${EMSOFT_hdf5LinkLibs} EMsoftHDFLib EMsoftLib)
    
      Add_EMsoft_Executable(TARGET EMoSLERP
                                    SOURCES ${APP_DIR}/EMoSLERP.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    TEMPLATE ${TMPLT_DIR}/EMoSLERP.template 
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMsoftSlackTest
                                    SOURCES ${APP_DIR}/EMsoftSlackTest.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMDisorientations
                                    SOURCES ${APP_DIR}/EMDisorientations.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMDisorientationsTwoPhase
                                    SOURCES ${APP_DIR}/EMDisorientationsTwoPhase.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMConvertOrientations
                                    SOURCES ${APP_DIR}/EMConvertOrientations.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMeqvrot
                                    SOURCES ${APP_DIR}/EMeqvrot.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

     Add_EMsoft_Executable(TARGET EMeqvPS
                                    SOURCES ${APP_DIR}/EMeqvPS.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMqg 
                                    SOURCES ${APP_DIR}/EMqg.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMshowxtal
                                    SOURCES ${APP_DIR}/EMshowxtal.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMstar 
                                    SOURCES ${APP_DIR}/EMstar.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMorbit 
                                    SOURCES ${APP_DIR}/EMorbit.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMzap 
                                    SOURCES ${APP_DIR}/EMzap.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMZAgeom 
                                    SOURCES ${APP_DIR}/EMZAgeom.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMorient 
                                    SOURCES ${APP_DIR}/EMorient.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMlatgeom 
                                    SOURCES ${APP_DIR}/EMlatgeom.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMstereo 
                                    SOURCES ${APP_DIR}/EMstereo.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMmkxtal 
                                    SOURCES ${APP_DIR}/EMmkxtal.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMxtalExtract 
                                    SOURCES ${APP_DIR}/EMxtalExtract.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMdrawcell 
                                    SOURCES ${APP_DIR}/EMdrawcell.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMKikuchiMap 
                                    SOURCES ${APP_DIR}/EMKikuchiMap.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMfamily 
                                    SOURCES ${APP_DIR}/EMfamily.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMxtalinfo 
                                    SOURCES ${APP_DIR}/EMxtalinfo.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMsoft_Executable(TARGET EMHOLZ 
                                    SOURCES ${APP_DIR}/EMHOLZ.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)

      Add_EMSoft_Executable(TARGET EMmergefiles
                                    SOURCES ${APP_DIR}/EMmergefiles.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)
      Add_EMSoft_Executable(TARGET EMsampleRFZ 
                                    SOURCES ${APP_DIR}/EMsampleRFZ.f90 
                                    LINK_LIBRARIES ${EXE_LINK_LIBRARIES}
                                    SOLUTION_FOLDER EMsoftPublic/Utilities 
                                    INSTALL_PROGRAM TRUE)


endif()

Add_EMsoft_Executable(TARGET EMlistSG 
                              SOURCES ${APP_DIR}/EMlistSG.f90 
                              LINK_LIBRARIES EMsoftLib
                              SOLUTION_FOLDER EMsoftPublic/Utilities 
                              INSTALL_PROGRAM TRUE)

Add_EMSoft_Executable(TARGET EMOpenCLinfo 
                              SOURCES ${APP_DIR}/EMOpenCLinfo.f90 
                              LINK_LIBRARIES EMsoftLib
                              SOLUTION_FOLDER EMsoftPublic/Utilities 
                              INSTALL_PROGRAM TRUE)
Add_EMsoft_Executable(TARGET EMsoftinit 
                              SOURCES ${APP_DIR}/EMsoftinit.f90 
                              LINK_LIBRARIES EMsoftLib
                              SOLUTION_FOLDER EMsoftPublic/Utilities 
                              INSTALL_PROGRAM TRUE)

