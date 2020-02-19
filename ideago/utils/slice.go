package utils

func CopySliceByte(src []byte) (dst []byte) {
	dst = make([]byte, len(src))
	copy(dst, src)
	return
}
