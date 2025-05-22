cmake_minimum_required(VERSION 3.19)
project(Kolokwiarz LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Kolokwiarz
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    core/question.h core/question.cpp
    core/textquestion.h core/textquestion.cpp
    core/textquestion.cpp core/textquestion.h
    core/QuestionSource.h
    core/jsonquestionsource.h core/jsonquestionsource.cpp
    core/quizmanager.h core/quizmanager.cpp
    base/miernictwoForTesting.json
    core/user.h core/user.cpp
    core/admin.h core/admin.cpp
    core/questioneditor.h core/questioneditor.cpp
    core/usermanager.h core/usermanager.cpp
    gui/loginwindow.h gui/loginwindow.cpp gui/loginwindow.ui
    gui/quizwindow.h gui/quizwindow.cpp gui/quizwindow.ui
    gui/rankingwindow.h gui/rankingwindow.cpp gui/rankingwindow.ui
)

target_link_libraries(Kolokwiarz
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Kolokwiarz
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Kolokwiarz
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
