package main

import (
	"log"
	"reflect"
	"strings"
	"unsafe"
)

func testReflect() {
	d := DocExt{}
	d.Int1 = 1
	d.Int2 = 22
	d.Arr5 = [10]int{1, 2, 3, 4, 5}
	d.Int7 = 7
	d.Doc.Int2 = 4
	for i := 0; i < 3 && i < 10; i++ {
		d.Doc.Arr5[i] = d.Arr5[i]
	}

	log.Printf("%+v", d)

	v := reflect.TypeOf(d)
	log.Println("+++++++++++++")
	tt, ff, kk, ii := getStructInfo(d)
	log.Printf("%q %q %v %v", tt, ff, kk, ii)
	log.Println("+++++++++++++")
	for i := 0; i < v.NumField(); i++ {
		printField(v.Field(i))
	}
	log.Println(unsafe.Sizeof(d))

	log.Println(v.NumField())
	for i := 0; i < v.NumField(); i++ {
		log.Printf("%d %+v", i, v.Field(i))
	}
	log.Println(v.FieldByName("int1"))
	log.Println(v.FieldByName("Int1"))
	log.Println(v.FieldByNameFunc(func(s string) bool {
		return strings.ToLower(s) == strings.ToLower("INT1")
	}))
	f, o := v.FieldByName("Int1")
	log.Printf("%+v %v", f, o)
	log.Printf("%+v", v.FieldByIndex(f.Index))

	v2 := reflect.ValueOf(&d)
	v3 := v2.Elem()
	f4 := v3.FieldByIndex(f.Index)
	f4.SetInt(999)
	log.Printf("%+v", d)

	d5 := Doc{}
	d6 := DocExt{}
	d5 = d.Doc
	d6 = d
	log.Println(d5, d6)
}

type Doc struct {
	Int1 int    `tag:"a1"`
	Int2 int    `tag:"a2"`
	Int3 int    `tag:"a3"`
	Int4 int    `tag:"a4"`
	Arr5 [3]int `tag:"a5"`
}

type DocExt struct {
	Doc
	Int2 int
	Int7 int `tag:"a7"`
	Arr5 [10]int
}

func printField(f reflect.StructField) {
	if f.Type.Kind() == reflect.Struct {
		for i := 0; i < f.Type.NumField(); i++ {
			printField(f.Type.Field(i))
		}
	} else {
		log.Println(f.Name, f.Index)
	}
}

func getFieldInfo(f reflect.StructField, tags, fields *[]string, kinds *[]reflect.Kind) {
	if f.Type.Kind() == reflect.Struct {
		for i := 0; i < f.Type.NumField(); i++ {
			getFieldInfo(f.Type.Field(i), tags, fields, kinds)
		}
	} else {
		*tags = append(*tags, strings.ToLower(f.Tag.Get("tag")))
		*fields = append(*fields, f.Name)
		*kinds = append(*kinds, f.Type.Kind())
	}
}

func getStructInfo(pItem interface{}) (tags, fields []string, kinds []reflect.Kind, indexes [][]int) {
	v := reflect.TypeOf(pItem)
	if v.Kind() == reflect.Ptr {
		v = v.Elem()
	}
	for i := 0; i < v.NumField(); i++ {
		getFieldInfo(v.Field(i), &tags, &fields, &kinds)
	}
	for i, fn := range fields {
		f, ok := v.FieldByName(fn)
		if !ok {
			panic("invalid field found")
		}
		log.Printf("!!! %s %+v", fn, f)
		indexes = append(indexes, f.Index)
		fields[i] = strings.ToLower(fn)
	}
	return
}

func getFieldInfoV2(f reflect.StructField, index []int, tags, fields *[]string, kinds *[]reflect.Kind, indexes *[][]int) {
	if f.Type.Kind() == reflect.Struct {
		for i := 0; i < f.Type.NumField(); i++ {
			var index2 []int
			index2 = append(index2, index...)
			index2 = append(index2, i)
			getFieldInfoV2(f.Type.Field(i), index2, tags, fields, kinds, indexes)
		}
	} else {
		*tags = append(*tags, strings.ToLower(f.Tag.Get("tag")))
		*fields = append(*fields, strings.ToLower(f.Name))
		*kinds = append(*kinds, f.Type.Kind())
		*indexes = append(*indexes, index)
	}
}

func getStructInfoV2(pItem interface{}) (tags, fields []string, kinds []reflect.Kind, indexes [][]int) {
	v := reflect.TypeOf(pItem)
	if v.Kind() == reflect.Ptr {
		v = v.Elem()
	}
	for i := 0; i < v.NumField(); i++ {
		getFieldInfoV2(v.Field(i), []int{i}, &tags, &fields, &kinds, &indexes)
	}
	return
}

func testArr(p interface{}) (ok bool) {
	v := reflect.ValueOf(p)
	if v.Kind() != reflect.Ptr {
		return false
	}
	v = v.Elem()
	if v.Kind() != reflect.Array {
		return false
	}
	for i := 0; i < v.Len(); i++ {
		v.Index(i).SetInt(10 + int64(i))
	}
	return true
}
