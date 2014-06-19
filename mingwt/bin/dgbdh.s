# IMAGE_IMPORT_DESCRIPTOR
	.section	.idata$2
	.global	__head_libLPKernelEx_a
__head_libLPKernelEx_a:
	.rva	hname	#Ptr to image import by name list
	#this should be the timestamp, but NT sometimes
	#doesn't load DLLs when this is set.
	.long	0	# loaded time
	.long	0	# Forwarder chain
	.rva	__libLPKernelEx_a_iname	# imported dll's name
	.rva	fthunk	# pointer to firstthunk
#Stuff for compatibility
	.section	.idata$5
	.long	0
fthunk:
	.section	.idata$4
	.long	0
	.section	.idata$4
hname:
