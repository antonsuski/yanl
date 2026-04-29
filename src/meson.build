name = 'lib@0@'.format(
    meson.project_name(),
)

message(f'library name: @name@')

# dependencies
deps = []

src_files = files('yanl.cxx')

libyanl = library(name, src_files, include_directories: inc_dirs, dependencies: deps)

