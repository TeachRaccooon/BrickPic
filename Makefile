
CC = g++ 

SOURCE_NAME = dotter
JGRAPH_NAME_0 = Stadium_Dense
JGRAPH_NAME_1 = Stadium
JGRAPH_NAME_2 = Lisa
JGRAPH_NAME_3 = Max
JGRAPH_NAME_4 = Plank

OBJECT_FILES = $(SOURCE_NAME).o

$(SOURCE_NAME) : $(OBJECT_FILES)
	${CC} $(CFLAGS) -o $@ $(OBJECT_FILES)

$(SOURCE_NAME).o : $(SOURCE_NAME).cpp
	${CC} $(CFLAGS) -c $<

clean :
	$(RM) $(JGRAPH_NAME_0).jgr
	$(RM) $(JGRAPH_NAME_1).jgr
	$(RM) $(JGRAPH_NAME_2).jgr
	$(RM) $(JGRAPH_NAME_3).jgr
	$(RM) $(JGRAPH_NAME_4).jgr
	
	$(RM) $(JGRAPH_NAME_0).jpg
	$(RM) $(JGRAPH_NAME_1).jpg
	$(RM) $(JGRAPH_NAME_2).jpg
	$(RM) $(JGRAPH_NAME_3).jpg
	$(RM) $(JGRAPH_NAME_4).jpg

	$(RM) $(SOURCE_NAME)
	$(RM) $(OBJECT_FILES)

run :
	# Local run options commented out.
	$(RM) $(JGRAPH_NAME_1).jgr
	@$(MAKE) && ./$(SOURCE_NAME) 0.02 $(JGRAPH_NAME_1).ppm > $(JGRAPH_NAME_0).jgr
	#jgraph -P ${JGRAPH_NAME_0}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_0}.jpg
	/home/jplank/bin/LINUX-X86_64/jgraph -P ${JGRAPH_NAME_0}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_0}.jpg

	$(RM) $(JGRAPH_NAME_1).jgr
	@$(MAKE) && ./$(SOURCE_NAME) 0.1 $(JGRAPH_NAME_1).ppm > $(JGRAPH_NAME_1).jgr
	#jgraph -P ${JGRAPH_NAME_1}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_1}.jpg
	/home/jplank/bin/LINUX-X86_64/jgraph -P ${JGRAPH_NAME_1}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_1}.jpg

	$(RM) $(JGRAPH_NAME_2).jgr
	@$(MAKE) && ./$(SOURCE_NAME) 0.1 $(JGRAPH_NAME_2).ppm > $(JGRAPH_NAME_2).jgr
	#jgraph -P ${JGRAPH_NAME_2}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_2}.jpg
	/home/jplank/bin/LINUX-X86_64/jgraph -P ${JGRAPH_NAME_2}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_2}.jpg

	$(RM) $(JGRAPH_NAME_3).jgr
	@$(MAKE) && ./$(SOURCE_NAME) 0.03 $(JGRAPH_NAME_3).ppm > $(JGRAPH_NAME_3).jgr
	#jgraph -P ${JGRAPH_NAME_3}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_3}.jpg
	/home/jplank/bin/LINUX-X86_64/jgraph -P ${JGRAPH_NAME_3}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_3}.jpg

	$(RM) $(JGRAPH_NAME_4).jgr
	@$(MAKE) && ./$(SOURCE_NAME) 0.03 $(JGRAPH_NAME_4).ppm > $(JGRAPH_NAME_4).jgr
	#jgraph -P ${JGRAPH_NAME_4}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_4}.jpg
	/home/jplank/bin/LINUX-X86_64/jgraph -P ${JGRAPH_NAME_4}.jgr | ps2pdf - | convert -density 300 - -quality 100 ${JGRAPH_NAME_4}.jpg
