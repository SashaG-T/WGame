DOMAIN=gervaistourangeau.com
USER=bitnami
WEBROOT=/home/bitnami/apps/wordpress/htdocs
PUBDIR = wgame/demo
PPK="C:\Users\sasha\Documents\gervaistourangeau website\bitnami-aws-467635569666.ppk"

# ===============================================================================================

CC = emcc
COMMONFLAGS = -s USE_SDL=2 -s USE_SDL_IMAGE=2
PREFLAGS = -lSDL --preload-file Resources -s ALLOW_MEMORY_GROWTH=1 --use-preload-plugins -s SDL2_IMAGE_FORMATS="['bmp','png']" -s GL_UNSAFE_OPTS=0
POSTFLAGS = --shell-file shell_minimal.html -s LLD_REPORT_UNDEFINED
SOURCE = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,wobj/%.o,$(SOURCE))
MAIN = wbin/$(PUBDIR)/index.html

# ===============================================================================================

.PHONY: depend clean

all: $(MAIN)
	@echo Compilation finished!

wbin/$(PUBDIR):
	mkdir "$@"
	
wobj:
	mkdir "$@"

wobj/%.o: src/%.c | wobj
	$(CC) $(COMMONFLAGS) -c -o $@ $<

$(MAIN): $(OBJS) | wbin/$(PUBDIR)
	$(CC) $(COMMONFLAGS) $(PREFLAGS) -o $@ $^ $(POSTFLAGS)

clean:
	cmd /c del /F /S /Q wobj\*.*
	cmd /c del /F /S /Q wbin\*.*
	cmd /c rmdir /S /Q .\wobj
	cmd /c rmdir /S /Q .\wbin

publish:
	@echo Publishing to $(DOMAIN)...
	pscp -r -i $(PPK) "wbin/$(firstword $(subst /, ,$(PUBDIR)))" "$(USER)@$(DOMAIN):$(WEBROOT)/"
	@echo Done. Check $(DOMAIN)/$(PUBDIR) to confirm. (Remember to clear the cache first!)
