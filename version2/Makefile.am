SUBDIRS	= extradist src docs debian 
EXTRA_DIST = TODO run-free.spec run-free.spec.in am_rpm_init.m4

if MAKE_RPMS
rpm: @RPM_TARGET@
.PHONY: rpm
$(RPM_TARGET): $(DISTFILES)
	${MAKE} dist
	-mkdir -p $(RPM_DIR)/SRPMS
	-mkdir -p `dirname $(RPM_TARGET)`
	$(RPM_PROG) $(RPM_ARGS) $(RPM_TARBALL)
	@echo Congratulations, $(RPM_TARGET) "(and friends)" should now exist.
else
endif
