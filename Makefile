.PHONY: all
all: template

template: cp_files tar_files compress 

dirs:
	mkdir -p temp/assets
	mkdir -p temp/src

cp_files: dirs
	 cp -r assets/* temp/assets
	 cp src/* temp/src
	 cp template/* temp

tar_files: cp_files
	cd temp;tar rvf make_sdl2_c.tar *
	
compress: cp_files tar_files
	bzip2 -z --force temp/make_sdl2_c.tar

install: template
	cp temp/make_sdl2_c.tar.bz2 /home/$(USER)/.local/share/kdevappwizard/templates


.PHONY: clean
clean:
	@rm -rf temp 2>/dev/null || true

