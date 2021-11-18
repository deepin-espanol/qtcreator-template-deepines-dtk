PREFIX = /usr

all:

install:
	mkdir -p $(DESTDIR)$(PREFIX)/share/qtcreator/templates/wizards/projects
	cp -r deepines-dtk-application $(DESTDIR)$(PREFIX)/share/qtcreator/templates/wizards/projects/
	chmod 755 $(DESTDIR)$(PREFIX)/share/qtcreator/templates/wizards/projects/deepines-dtk-application