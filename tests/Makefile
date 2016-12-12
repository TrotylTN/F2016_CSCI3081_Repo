TARGET := ../build/bin/MIA
ORIGINDIR := $(shell pwd)/origin
TESTDIR := $(shell pwd)/test
GOLDENDIR := $(shell pwd)/golden

all-tests := $(addsuffix .test, pass invalid compare sharpen threshold quantize blur saturate edge channel chain batch help)
files-used := $(ORIGINDIR)/snaily.jpg $(ORIGINDIR)/colorCircles.png
test-files := $(files-used)
test-files += golden 1.txt
check-invalid := && ([ $$? -eq 0 ] && echo "success!") || echo failure!

bad-brainstack := $(addprefix $(TESTDIR)/bad-brainstack, $(shell seq 1 4))

all-golden := $(addsuffix .golden, pass sharpen threshold quantize blur saturate edge channel chain batch help)

.PHONY: *.test *.golden golden all test clean veryclean

all: tests

test: $(all-tests) | $(TESTDIR)
	@echo Success, all tests passed

invalid.test: $(test-files) | $(TESTDIR) $(bad-brainstack)
	@./$(TARGET) $(TESTDIR)/bad-input-extension.foo $(TESTDIR)/bad-input-extension.jpg $(check-invalid)
	@./$(TARGET) does/not/exist.jpg input-does-not-exist.jpg $(check-invalid)
	@./$(TARGET) $(word 2, $^) $(TESTDIR)/color-circles.foo $(check-invalid)
	@./$(TARGET) $(word 2, $^) does/not/exist.png $(check-invalid)
	@./$(TARGET) -sharpen 5.0 $(TESTDIR)/missing-input-file.png $(check-invalid)
	@./$(TARGET) $< -sharpen 5.0 $(check-invalid)
	@./$(TARGET) $< -compare 17 $(TESTDIR)/$(notdir $<) $(check-invalid)
	@./$(TARGET) $< -channel 1.0 1.0 $(TESTDIR)/bad-channel-parameters.png $(check-invalid)
	@./$(TARGET) $< -edge 5.0 $(TESTDIR)/bad-edge-parameters.png $(check-invalid)
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit##.png $(TESTDIR)/bad-brainstack1/mr-brain8bit##.png $(check-invalid)
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack2/mr-brain8bit##.png $(check-invalid)
	@./$(TARGET) $(ORIGINDIR)/brainstack/ $(TESTDIR)/bad-brainstack3/mr-brain8bit###.png $(check-invalid)
	@./$(TARGET) $(ORIGINDIR)/brainstack/mr-brain-8bit###.png $(TESTDIR)/bad-brainstack4/ $(check-invalid)
	@./$(TARGET) $< 12.12 $(TESTDIR)/only-numbers-arg.png $(check-invalid)
	@./$(TARGET) $< -blur -0.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -blur 20.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -threshold -0.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -threshold 1.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -quantize 1.999 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -quantize 256.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -sharpen 0.999 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -sharpen 100.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -saturate -10.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -saturate 10.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -channel -0.001 1 1 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -channel 1 10.001 10.001 $(TESTDIR)/out-of-bound.png $(check-invalid)
	@./$(TARGET) $< -edge -sharpen 10.0 -channel 10 -10 1 $(TESTDIR)/out-of-bound.png $(check-invalid)

blur.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png
	./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).png
	./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).png
	./$(TARGET) $(TESTDIR)/3$(basename $@).png -compare $(GOLDENDIR)/3$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(TESTDIR)/1$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(TESTDIR)/2$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/3$(basename $@).jpg -compare $(GOLDENDIR)/3$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(TESTDIR)/3$(basename $@).jpg; fi

threshold.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png
	./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).png
	./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).png
	./$(TARGET) $(TESTDIR)/3$(basename $@).png -compare $(GOLDENDIR)/3$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(TESTDIR)/0$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(TESTDIR)/1$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(TESTDIR)/2$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/3$(basename $@).jpg -compare $(GOLDENDIR)/3$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(TESTDIR)/3$(basename $@).jpg; fi

quantize.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -$(basename $@) 2 $(TESTDIR)/0$(basename $@).png
	./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 2 $(TESTDIR)/0$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 256 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 256 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(TESTDIR)/0$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(TESTDIR)/0$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(TESTDIR)/1$(basename $@).jpg; fi

sharpen.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -$(basename $@) 1 $(TESTDIR)/0$(basename $@).png
	./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 1 $(TESTDIR)/0$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(TESTDIR)/0$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(TESTDIR)/0$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(TESTDIR)/1$(basename $@).jpg; fi

saturate.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).png
	./$(TARGET) $(TESTDIR)/0$(basename $@).png -compare $(GOLDENDIR)/0$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 0 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 0 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $< -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).png
	./$(TARGET) $(TESTDIR)/2$(basename $@).png -compare $(GOLDENDIR)/2$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $< -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/0$(basename $@).jpg -compare $(GOLDENDIR)/0$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(TESTDIR)/0$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(GOLDENDIR)/1$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(TESTDIR)/1$(basename $@).jpg; fi
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo PASSED; else echo failed: ./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(TESTDIR)/2$(basename $@).jpg; fi

edge.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -edge $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $< -edge $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -edge $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $(word 2, $^) -edge $(TESTDIR)/2$(basename $@).jpg; fi

channel.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -channel 0 5.125 10.0 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $< -channel 0 5.125 10.0 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(TESTDIR)/2$(basename $@).jpg; fi

chain.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(GOLDENDIR)/1$(basename $@).png > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/1$(basename $@).png; fi
	./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/2$(basename $@).jpg -compare $(GOLDENDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(TESTDIR)/2$(basename $@).jpg; fi

compare.test: $(test-files)
	./$(TARGET) $< -compare $< > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $< -compare $<; fi
	./$(TARGET) $(word 2, $^) -compare $(word 2, $^) > out.log
	@if cmp -s out.log 1.txt; then echo passed; else echo failed: ./$(TARGET) $(word 2, $^) -compare $(word 2, $^); fi
	./$(TARGET) $< -compare $(word 2, $^) > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $< -compare $(word 2, $^); fi
	./$(TARGET) $< -blur 1.0 $(TESTDIR)/1$(basename $@).png
	./$(TARGET) $< -blur 1.0 $(TESTDIR)/2$(basename $@).png
	./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(TESTDIR)/2$(basename $@).png > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $(TESTDIR)/1$(basename $@).png -compare $(TESTDIR)/2$(basename $@).png; fi
	./$(TARGET) $< -blur 1.0 $(TESTDIR)/1$(basename $@).jpg
	./$(TARGET) $< -blur 1.0 $(TESTDIR)/2$(basename $@).jpg
	./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(TESTDIR)/2$(basename $@).jpg > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $(TESTDIR)/1$(basename $@).jpg -compare $(TESTDIR)/2$(basename $@).jpg; fi

help.test: $(GOLDENDIR)/help.txt
	./$(TARGET) -h > out.log
	@if cmp -s out.log help.txt; then echo passed; else echo failed ./$(TARGET) -h; fi

batch.test: $(ORIGINDIR)/brainstack $(GOLDENDIR)/brainstack | $(TESTDIR) $(TESTDIR)/edge $(TESTDIR)/quantize
	./$(TARGET) $</mrbrain-8bit###.png -edge $(TESTDIR)/edge/mrbrain-8bit###.png
	./$(TARGET) $(TESTDIR)/edge/mrbrain-8bit###.png -compare $(GOLDENDIR)/edge/mrbrain-8bit###.png > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $</mrbrain-8bit###.png -edge $(TESTDIR)/edge/mrbrain-8bit###.png; fi
	./$(TARGET) $</mrbrain-8bit###.png -quantize $(TESTDIR)/quantize/mrbrain-8bit###.png
	./$(TARGET) $(TESTDIR)/quantize/mrbrain-8bit###.png -compare $(GOLDENDIR)/quantize/mrbrain-8bit###.png > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $</mrbrain-8bit###.png -quantize $(TESTDIR)/quantize/mrbrain-8bit###.png; fi

pass.test: $(test-files) | $(TESTDIR)
	./$(TARGET) $< $(TESTDIR)/$(notdir $<)
	./$(TARGET) $(TESTDIR)/$(notdir $<) -compare $(GOLDENDIR)/$(notdir $<) > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $< $(TESTDIR)/$(notdir $<); fi
	./$(TARGET) $< $(TESTDIR)/$(notdir $(word 2, $^))
	./$(TARGET) $(TESTDIR)/$(notdir $(word 2, $^)) -compare $(GOLDENDIR)/$(notdir $(word 2, $^)) > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $< $(TESTDIR)/$(notdir $(word 2, $^)); fi
	./$(TARGET) $< $(TESTDIR)/$(basename $(notdir $<)).jpg
	./$(TARGET) $(TESTDIR)/$(basename $(notdir $<)).jpg -compare $(GOLDENDIR)/$(basename $(notdir $<)).jpg > out.log
	@if cmp -s out.log 0.txt; then echo passed; else echo failed: ./$(TARGET) $< $(TESTDIR)/$(basename $(notdir $<)).jpg; fi

# ---------- GOLDEN -------------- #
golden: $(shell pwd)/origin $(all-golden) | $(GOLDENDIR)

blur.golden: $(files-used)
	./$(TARGET) $< -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 5.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 10.246 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $< -$(basename $@) 20.0 $(GOLDENDIR)/3$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 5.0 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.246 $(GOLDENDIR)/2$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 20.0 $(GOLDENDIR)/3$(basename $@).jpg

threshold.golden: $(files-used)
	./$(TARGET) $< -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0.1 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0.82436 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $< -$(basename $@) 1.0 $(GOLDENDIR)/3$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.1 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0.82436 $(GOLDENDIR)/2$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 1.0 $(GOLDENDIR)/3$(basename $@).jpg

quantize.golden: $(files-used)
	./$(TARGET) $< -$(basename $@) 2 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 256 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 2 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 256 $(GOLDENDIR)/1$(basename $@).jpg

sharpen.golden: $(files-used)
	./$(TARGET) $< -$(basename $@) 1 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 100.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) 1 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 100.0 $(GOLDENDIR)/1$(basename $@).jpg

saturate.golden: $(files-used)
	./$(TARGET) $< -$(basename $@) -10.0 $(GOLDENDIR)/0$(basename $@).png
	./$(TARGET) $< -$(basename $@) 0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $< -$(basename $@) 10.0 $(GOLDENDIR)/2$(basename $@).png
	./$(TARGET) $(word 2, $^) -$(basename $@) -10.0 $(GOLDENDIR)/0$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 0 $(GOLDENDIR)/1$(basename $@).jpg
	./$(TARGET) $(word 2, $^) -$(basename $@) 10.0 $(GOLDENDIR)/2$(basename $@).jpg

edge.golden: $(files-used)
	./$(TARGET) $< -edge $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -edge $(GOLDENDIR)/2$(basename $@).jpg

channel.golden: $(files-used)
	./$(TARGET) $< -channel 0 5.125 10.0 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -channel 0 5.125 10.0 $(GOLDENDIR)/2$(basename $@).jpg

chain.golden: $(files-used)
	./$(TARGET) $< -saturate 0 -threshold 0.8 -quantize 2 $(GOLDENDIR)/1$(basename $@).png
	./$(TARGET) $(word 2, $^) -saturate 0 -threshold 0.8 -quantize 2 $(GOLDENDIR)/2$(basename $@).jpg

help.golden:
	./$(TARGET) -h > $(GOLDENDIR)/help.txt

batch.golden: $(ORIGINDIR)/brainstack
	./$(TARGET) $</mrbrain-8bit###.png -edge $(GOLDENDIR)/edge/mrbrain-8bit###.png
	./$(TARGET) $</mrbrain-8bit###.png -quantize $(GOLDENDIR)/quantize/mrbrain-8bit###.png

pass.golden: $(files-used) | $(GOLDENDIR)/edge $(GOLDENDIR)/quantize
	./$(TARGET) $< $(GOLDENDIR)/$(notdir $<)
	./$(TARGET) $< $(GOLDENDIR)/$(notdir $(word 2, $^))
	./$(TARGET) $< $(GOLDENDIR)/$(basename $(notdir $<)).jpg

$(TESTDIR) $(GOLDENDIR) $(TESTDIR)/edge $(TESTDIR)/quantize $(GOLDENDIR)/edge $(GOLDENDIR)/quantize $(bad-brainstack):
	mkdir -p $@

clean:
	rm -rf $(TESTDIR)

veryclean: clean
	rm -rf $(GOLDENDIR)
