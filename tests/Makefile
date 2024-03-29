TARGET := ../build/bin/MIA
ORIGINDIR := $(shell pwd)/origin
TESTDIR := $(shell pwd)/test
GOLDENDIR := $(shell pwd)/golden

all-tests := $(addsuffix .test, pass invalid compare threshold quantize blur saturate edge channel sharpen chain batch help)
files-used := $(ORIGINDIR)/snaily.jpg $(ORIGINDIR)/colorCircles.png
test-files := $(files-used)
test-files += $(GOLDENDIR) 1.txt
check-invalid := && ([ $$? -eq 0 ] && echo -n "FAILED: ") || echo -n "PASSED: "
compare-check-1 := @if cmp -s out.log 1.txt; then echo -n "PASSED: "; else echo -n "FAILED: "; fi
compare-check-0 := @if cmp -s out.log 0.txt; then echo -n "PASSED: "; else echo -n "FAILED: "; fi
compare-check-1-99 := @if cmp -s out.log 99-1.txt; then echo -n "PASSED: "; else echo -n "FAILED: "; fi

bad-brainstack := $(addprefix $(TESTDIR)/bad-brainstack, $(shell seq 1 4))

all-golden := $(addsuffix .golden, pass threshold quantize blur saturate edge channel sharpen chain batch help)

.PHONY: *.test *.golden golden all test clean veryclean

all: test

test: $(all-tests) | $(TESTDIR)
	@echo Done all tests

invalid.test: $(test-files) | $(TESTDIR) $(bad-brainstack)
	@./$(TARGET) $(TESTDIR)/bad-input-extension.foo $(TESTDIR)/bad-input-extension.jpg > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(TESTDIR)/bad-input-extension.foo $(TESTDIR)/bad-input-extension.jpg
	@./$(TARGET) does/not/exist.jpg input-does-not-exist.jpg > junk.txt $(check-invalid)
	@echo ./$(TARGET) does/not/exist.jpg input-does-not-exist.jpg
	@./$(TARGET) $(word 2, $^) $(TESTDIR)/color-circles.foo > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(word 2, $^) $(TESTDIR)/color-circles.foo
	@./$(TARGET) $(word 2, $^) does/not/exist.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(word 2, $^) does/not/exist.png
	@./$(TARGET) -sharpen 5.0 $(TESTDIR)/missing-input-file.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) -sharpen 5.0 $(TESTDIR)/missing-input-file.png
	@./$(TARGET) $< -sharpen 5.0 > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -sharpen 5.0
	@./$(TARGET) $< -compare 17 $(TESTDIR)/$(notdir $<) > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -compare 17 $(TESTDIR)/$(notdir $<)
	@./$(TARGET) $< -edge -compare $(TESTDIR)/invalid_combination.jpg > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -edge -compare $(TESTDIR)/invalid_combination.jpg
	@./$(TARGET) $< -channel 1.0 1.0 $(TESTDIR)/bad-channel-parameters.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -channel 1.0 1.0 $(TESTDIR)/bad-channel-parameters.png
	@./$(TARGET) $< -edge 5.0 $(TESTDIR)/bad-edge-parameters.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -edge 5.0 $(TESTDIR)/bad-edge-parameters.png
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit##.png $(TESTDIR)/bad-brainstack1/mr-brain8bit##.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit##.png $(TESTDIR)/bad-brainstack1/mr-brain8bit##.png
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack2/mr-brain8bit##.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack2/mr-brain8bit##.png
	@./$(TARGET) $(ORIGINDIR)/brainstack/ $(TESTDIR)/bad-brainstack3/mr-brain8bit###.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(ORIGINDIR)/brainstack/ $(TESTDIR)/bad-brainstack3/mr-brain8bit###.png
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack4/ > junk.txt $(check-invalid)
	@echo ./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack4/
	@./$(TARGET) $< 12.12 $(TESTDIR)/only-numbers-arg.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< 12.12 $(TESTDIR)/only-numbers-arg.png
	@./$(TARGET) $< -blur -0.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -blur -0.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -blur 20.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -blur 20.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -threshold -0.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -threshold -0.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -threshold 1.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -threshold 1.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -quantize 1.999 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -quantize 1.999 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -quantize 256.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -quantize 256.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -sharpen 0.999 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -sharpen 0.999 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -sharpen 100.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -sharpen 100.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -saturate -10.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -saturate -10.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -saturate 10.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -saturate 10.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -channel -0.001 1 1 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -channel -0.001 1 1 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -channel 1 10.001 10.001 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -channel 1 10.001 10.001 $(TESTDIR)/out-of-bound.png
	@./$(TARGET) $< -edge -sharpen 10.0 -channel 10 -10 1 $(TESTDIR)/out-of-bound.png > junk.txt $(check-invalid)
	@echo ./$(TARGET) $< -edge -sharpen 10.0 -channel 10 -10 1 $(TESTDIR)/out-of-bound.png

blur.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/3$(basename $@).png -compare $(GOLDENDIR)/3$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).png
	@./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/3$(basename $@).jpg -compare $(GOLDENDIR)/3$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).jpg

threshold.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/3$(basename $@).png -compare $(GOLDENDIR)/3$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).png
	@./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/3$(basename $@).jpg -compare $(GOLDENDIR)/3$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).jpg

quantize.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -$(basename $@) 2 $(TESTDIR)/0$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 2 $(TESTDIR)/0$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 256 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 256 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(TESTDIR)/0$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(TESTDIR)/0$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(TESTDIR)/1$(basename $@).jpg

sharpen.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -$(basename $@) 1 $(TESTDIR)/0$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 1 $(TESTDIR)/0$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(TESTDIR)/0$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(TESTDIR)/0$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).jpg

saturate.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 0 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 0 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $< -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).png
	@./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(TESTDIR)/1$(basename $@).jpg
	@./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).jpg

edge.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -edge $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo ./$(TARGET) $< -edge $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $(word 2, $^) -edge $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -edge $(TESTDIR)/2$(basename $@).jpg

channel.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -channel 0 5.125 10.0 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -channel 0 5.125 10.0 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(TESTDIR)/2$(basename $@).jpg

chain.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/1$(basename $@).png
	@./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/2$(basename $@).jpg

compare.test: $(test-files)
	@./$(TARGET) $< -compare $< > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< -compare $<
	@./$(TARGET) $(word 2, $^) -compare $(word 2, $^) > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(word 2, $^) -compare $(word 2, $^)
	@./$(TARGET) $< -compare $(word 2, $^) > out.log
	$(compare-check-0)
	@echo  ./$(TARGET) $< -compare $(word 2, $^)
	@./$(TARGET) $< -blur 1.0 $(TESTDIR)/1$(basename $@).png > junk.txt
	@./$(TARGET) $< -blur 1.0 $(TESTDIR)/2$(basename $@).png > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(TESTDIR)/2$(basename $@).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(TESTDIR)/2$(basename $@).png
	@./$(TARGET) $< -blur 1.0 $(TESTDIR)/1$(basename $@).jpg > junk.txt
	@./$(TARGET) $< -blur 1.0 $(TESTDIR)/2$(basename $@).jpg > junk.txt
	@./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(TESTDIR)/2$(basename $@).jpg > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(TESTDIR)/2$(basename $@).jpg

help.test: $(GOLDENDIR)/help.txt
	@./$(TARGET) -h > out.log
	@if cmp -s out.log $(GOLDENDIR)/help.txt; then echo -n "PASSED: "; else echo -n "FAILED: "; fi
	@echo ./$(TARGET) -h

batch.test: $(ORIGINDIR)/brainstack $(GOLDENDIR)/edge $(GOLDENDIR)/quantize | $(TESTDIR) $(TESTDIR)/edge $(TESTDIR)/quantize
	@./$(TARGET) $</mrbrain-8bit###.png -edge $(TESTDIR)/edge/mrbrain-8bit###.png > junk.txt
	@./$(TARGET) $(TESTDIR)/edge/mrbrain-8bit###.png -compare $(GOLDENDIR)/edge/mrbrain-8bit###.png > out.log
	$(compare-check-1-99)
	@echo  ./$(TARGET) $</mrbrain-8bit###.png -edge $(TESTDIR)/edge/mrbrain-8bit###.png;
	@./$(TARGET) $</mrbrain-8bit###.png -quantize 4 $(TESTDIR)/quantize/mrbrain-8bit###.png > junk.txt
	@./$(TARGET) $(TESTDIR)/quantize/mrbrain-8bit###.png -compare $(GOLDENDIR)/quantize/mrbrain-8bit###.png > out.log
	$(compare-check-1-99)
	@echo  ./$(TARGET) $</mrbrain-8bit###.png -quantize 4 $(TESTDIR)/quantize/mrbrain-8bit###.png;

pass.test: $(test-files) | $(TESTDIR)
	@./$(TARGET) $< $(TESTDIR)/$(notdir $<) > junk.txt
	@./$(TARGET) $(TESTDIR)/$(notdir $<) -compare $(GOLDENDIR)/$(notdir $<) > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< $(TESTDIR)/$(notdir $<)
	@./$(TARGET) $(word 2, $^) $(TESTDIR)/$(notdir $(word 2, $^)) > junk.txt
	@./$(TARGET) $(TESTDIR)/$(notdir $(word 2, $^)) -compare $(GOLDENDIR)/$(notdir $(word 2, $^)) > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< $(TESTDIR)/$(notdir $(word 2, $^))
	@./$(TARGET) $< $(TESTDIR)/$(basename $(notdir $<)).png > junk.txt
	@./$(TARGET) $(TESTDIR)/$(basename $(notdir $<)).png -compare $(GOLDENDIR)/$(basename $(notdir $<)).png > out.log
	$(compare-check-1)
	@echo  ./$(TARGET) $< $(TESTDIR)/$(basename $(notdir $<)).png

# ---------- GOLDEN -------------- #
golden: $(shell pwd)/origin $(all-golden) | $(GOLDENDIR)
	@echo Golden images production completed.

blur.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 5.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 10.246 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $< -$(basename $@) 20.0 $(GOLDENDIR)/3$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(GOLDENDIR)/2$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(GOLDENDIR)/3$(basename $@).jpg

threshold.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0.1 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0.82436 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $< -$(basename $@) 1.0 $(GOLDENDIR)/3$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(GOLDENDIR)/2$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(GOLDENDIR)/3$(basename $@).jpg

quantize.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -$(basename $@) 2 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 256 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(GOLDENDIR)/1$(basename $@).jpg

sharpen.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -$(basename $@) 1 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 100.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(GOLDENDIR)/1$(basename $@).jpg

saturate.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -$(basename $@) -10.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 10.0 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(GOLDENDIR)/2$(basename $@).jpg

edge.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -edge $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -edge $(GOLDENDIR)/2$(basename $@).jpg

channel.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -channel 0 5.125 10.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(GOLDENDIR)/2$(basename $@).jpg

chain.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(GOLDENDIR)/2$(basename $@).jpg

help.golden: | $(GOLDENDIR)
	./$(TARGET) -h > $(GOLDENDIR)/help.txt

batch.golden: $(ORIGINDIR)/brainstack | $(GOLDENDIR) $(GOLDENDIR)/edge $(GOLDENDIR)/quantize
	./$(TARGET) $</mrbrain-8bit###.png -edge $(GOLDENDIR)/edge/mrbrain-8bit###.png
	./$(TARGET) $</mrbrain-8bit###.png -quantize 4 $(GOLDENDIR)/quantize/mrbrain-8bit###.png

pass.golden: $(files-used) | $(GOLDENDIR)
	./$(TARGET) $< $(GOLDENDIR)/$(notdir $<)
	./$(TARGET) $(word 2, $^) $(GOLDENDIR)/$(notdir $(word 2, $^))
	./$(TARGET) $< $(GOLDENDIR)/$(basename $(notdir $<)).png

$(TESTDIR) $(GOLDENDIR) $(TESTDIR)/edge $(TESTDIR)/quantize $(GOLDENDIR)/edge $(GOLDENDIR)/quantize $(bad-brainstack):
	mkdir -p $@

clean:
	rm -rf $(TESTDIR)

veryclean: clean
	rm -rf $(GOLDENDIR)
