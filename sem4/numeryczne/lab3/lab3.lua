open("diametral_magn.fem")

mi_createmesh()
mi_analyze()
mi_loadsolution()

mo_showdensityplot(1,0,0.848488092770747,0.0072542167670558,"bmag")

mi_savemetafile("dm_fd_1")

mo_addcontour(0,0)
mo_addcontour(5,0)
mo_makeplot(1,1000)

mi_selectgroup(2)
mi_scale(0,0,0.8,4)
mi_selectgroup(3)
mi_scale(0,0,0.8,4)
mi_savemetafile("cs_dm_1")

mi_createmesh()
mi_analyze()
mi_loadsolution()

mo_showdensityplot(1,0,0.848488092770747,0.0072542167670558,"bmag")
mo_addcontour(0,0)
mo_addcontour(5,0)
mo_makeplot(1,1000)

mi_savemetafile("cs_dm_2")