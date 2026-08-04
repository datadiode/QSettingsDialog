qt_add_executable(EngineTest WIN32 MACOSX_BUNDLE
    delayedtestentry.cpp delayedtestentry.h
    main.cpp
    swidget.cpp swidget.h
    testentry.cpp testentry.h
)
target_include_directories(EngineTest PRIVATE
    .././../QSettingsDialog
    .././../QSettingsDialog/core
    .././../QSettingsDialog/dialogui
    .././../QSettingsDialog/loaders
    .././../QSettingsDialog/variantwidgets
)

target_link_libraries(EngineTest PRIVATE
    Qt::Concurrent
    Qt::Core
    Qt::Gui
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(EngineTest PRIVATE
        Qt::Widgets
    )
endif()

target_link_directories(EngineTest PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/.././../../QSettingsDialog/$<CONFIG>
)

target_link_libraries(EngineTest PRIVATE
	QSettingsDialog
)

install(TARGETS EngineTest
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET EngineTest
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
