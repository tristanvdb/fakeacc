.PHONY: viz viz-mfb viz-mdcg

viz: viz-mfb viz-mdcg

viz-mfb:
	make -C MFB bin
	make -C MFB check

viz-mdcg:
	make -C MDCG bin
	make -C MDCG check

clean:
	make -C MFB clean
	make -C MDCG clean
