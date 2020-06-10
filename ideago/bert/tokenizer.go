package main

import "unicode/utf8"

const (
	tokenPad  = ""       //# Token for padding
	tokenUnk  = "[UNK]"  //# Token for unknown words
	tokenCls  = "[CLS]"  //# Token for classification
	tokenSep  = "[SEP]"  //# Token for separation
	tokenMask = "[MASK]" //# Token for masking
)

type Tokenizer struct {
	dict    map[string]int
	invDict map[int]string
	cls     string
	sep     string
	unk     string
	padIdx  int
	cased   bool
}

func NewTokenizer(dic map[string]int, padIdx int, cased bool) (t *Tokenizer) {
	dict := make(map[string]int, len(dic))
	invDict := make(map[int]string, len(dic))
	for k, v := range dic {
		dict[k] = v
		invDict[v] = k
	}

	t = &Tokenizer{
		dict:    dict,
		invDict: invDict,
		cls:     tokenCls,
		sep:     tokenSep,
		unk:     tokenUnk,
		padIdx:  padIdx,
		cased:   cased,
	}
	return
}

func (t *Tokenizer) wordPieceTokenize(word string) (tokens []string) {
	if _, ok := t.dict[word]; ok {
		return []string{word}
	}
	var start, stop int
	strLen := utf8.RuneCountInString(word)
	for start < strLen {

	}

}
