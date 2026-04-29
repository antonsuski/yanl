project('yanl', 'cpp')

src_dir = 'src'
inc_dir = 'include'

version = meson.project_version()
versions = version.split('.')
config = {'version': version, 'build_pref': ''}

message(f'Build version: @version@')

if version == 'undefined'
    config += {'v_major' : 0}
    config += {'v_minor' : 0}
    config += {'v_patch' : 0}
    config += {'build_suf' : '_dev'}
elif
    config += {'v_major' : versions[0].to_int()}
    config += {'v_minor' : versions[1].to_int()}
    config += {'v_patch' : versions[2].to_int()}
    config += {'build_suf' : '_rc'}
endif

configure_file(
    input: 'version.yaml.in',
    output: 'version.yaml',
    configuration: config,
)

subdir(inc_dir)
subdir(src_dir)

