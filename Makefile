.PHONY: all
all: template

template: cp_files tar_files compress

cp_files:
	 cp -r assets temp
	 cp -r src temp
	 cp template/* temp

tar_files: cp_files
	cd temp;tar rvf make_sdl2_c.tar *
	
compress: cp_files tar_files
	bzip2 -z --force temp/make_sdl2_c.tar

install: template
	mv temp/make_sdl2_c.tar.bz2 /home/$(USER)/.local/share/kdevappwizard/templates


.PHONY: clean
clean:
	@rm -rf temp 2>/dev/null || true

