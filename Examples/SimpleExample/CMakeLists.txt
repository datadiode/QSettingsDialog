qt_add_executable(SimpleExample WIN32 MACOSX_BUNDLE
    main.cpp
)
target_include_directories(SimpleExample PRIVATE
    .././../QSettingsDialog
    .././../QSettingsDialog/core
    .././../QSettingsDialog/dialogui
    .././../QSettingsDialog/loaders
    .././../QSettingsDialog/variantwidgets
)

target_link_libraries(SimpleExample PRIVATE
    Qt::Core
    Qt::Gui
	Qt::Widgets
)

target_link_directories(SimpleExample PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/.././../../QSettingsDialog/$<CONFIG>
)

target_link_libraries(SimpleExample PRIVATE
	QSettingsDialog
)

install(TARGETS SimpleExample
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET SimpleExample
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
