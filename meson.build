project('thrds', 'c', version:'1.0')

cc     = meson.get_compiler('c')
thrds_version_str = get_option('major_version').to_string() + '.' + get_option('minor_version').to_string()

SRCS=[
'src/mtx_init.c',
'src/mtx_destroy.c',
'src/mtx_lock.c',
'src/mtx_trylock.c',
'src/mtx_unlock.c',
'src/call_once.c',
'src/cnd_init.c',
'src/cnd_destroy.c',
'src/cnd_broadcast.c',
'src/cnd_signal.c',
'src/cnd_wait.c',
'src/cnd_timedwait.c',
'src/tss_create.c',
'src/tss_delete.c',
'src/tss_set.c',
'src/tss_get.c',
'src/thrd_create.c',
'src/thrd_exit.c',
'src/thrd_current.c',
'src/thrd_detach.c',
'src/thrd_join.c',
'src/thrd_equal.c',
'src/thrd_sleep.c',
'src/rwmtx_init.c',
'src/rwmtx_destroy.c',
'src/rwmtx_rdlock.c',
'src/rwmtx_wrlock.c',
'src/rwmtx_tryrdlock.c',
'src/rwmtx_trywrlock.c',
'src/rwmtx_unlock.c',
]

# For standard pthread implementations
POSIX_SRCS=[
'src/mtx_timedlock.c',

'src/thrd_yield.c',

'src/rwmtx_timedrdlock.c',
'src/rwmtx_timedwrlock.c',

'src/smtx_init.c',
'src/smtx_destroy.c',
'src/smtx_lock.c',
'src/smtx_unlock.c',
'src/smtx_trylock.c',

'src/bar_init.c',
'src/bar_destroy.c',
'src/bar_wait.c'
]

# For Apple
MACOS_SRCS=[
'src/macos/mtx_timedlock.c',

'src/macos/thrd_yield.c',

'src/macos/rwmtx_timedrdlock.c',
'src/macos/rwmtx_timedwrlock.c',

'src/macos/smtx_init.c',
'src/macos/smtx_destroy.c',
'src/macos/smtx_lock.c',
'src/macos/smtx_unlock.c',
'src/macos/smtx_trylock.c',

'src/macos/bar_init.c',
'src/macos/bar_destroy.c',
'src/macos/bar_wait.c'
]

MANPAGES=[
'man/mtx_init.3',
'man/mtx_destroy.3',
'man/mtx_lock.3',
'man/mtx_timedlock.3',
'man/mtx_trylock.3',
'man/mtx_unlock.3',
'man/call_once.3',
'man/cnd_init.3',
'man/cnd_destroy.3',
'man/cnd_broadcast.3',
'man/cnd_signal.3',
'man/cnd_wait.3',
'man/cnd_timedwait.3',
'man/tss_create.3',
'man/tss_delete.3',
'man/tss_set.3',
'man/tss_get.3',
'man/thrd_create.3',
'man/thrd_exit.3',
'man/thrd_current.3',
'man/thrd_detach.3',
'man/thrd_join.3',
'man/thrd_equal.3',
'man/thrd_sleep.3',
'man/thrd_yield.3',
'man/smtx_init.3',
'man/smtx_destroy.3',
'man/smtx_lock.3',
'man/smtx_unlock.3',
'man/smtx_trylock.3',
'man/rwmtx_init.3',
'man/rwmtx_destroy.3',
'man/rwmtx_rdlock.3',
'man/rwmtx_wrlock.3',
'man/rwmtx_tryrdlock.3',
'man/rwmtx_trywrlock.3',
'man/rwmtx_timedrdlock.3',
'man/rwmtx_timedwrlock.3',
'man/rwmtx_unlock.3',
'man/bar_init.3',
'man/bar_destroy.3',
'man/bar_wait.3',
]

if target_machine.system() == 'darwin'
  SRCS += MACOS_SRCS
else
  SRCS += POSIX_SRCS
endif

install_man(MANPAGES)

install_headers('src/threads.h', subdir: 'aethrds')
install_headers('src/threadse.h', subdir: 'aethrds')

both_libraries('aethrds', SRCS,
               soversion: thrds_version_str,
               install: true,
               include_directories: 'src')

if get_option('debug_version')
  both_libraries('aethrds_dbg', SRCS,
                 soversion: thrds_version_str,
                 install: true,
                 include_directories: 'src',
                 c_args : '-g')
endif
