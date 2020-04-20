package main

import (
	"reflect"
	"testing"
)

func Test_parseLogMsg(t *testing.T) {
	msg := "check_point_feature: 1587091280694216153983 score 40566546 0.0038456554 [3.0879004 1.0358167]"
	data, ok := parseLogMsg(msg)
	if !ok {
		t.Errorf("parseLogMsg() return false")
	}
	want := dnnData{
		input: []float32{3.0879004, 1.0358167},
		score: 0.0038456554,
		req:   "1587091280694216153983",
		doc:   "40566546",
	}

	if !reflect.DeepEqual(want, data) {
		t.Errorf("parseLogMsg() expect %v got %v", want, data)
	}

	/*
		type args struct {
			msg string
		}
		tests := []struct {
			name     string
			args     args
			wantData dnnData
		}{
		}
		for _, tt := range tests {
			t.Run(tt.name, func(t *testing.T) {
				if gotData := parseLogMsg(tt.args.msg); !reflect.DeepEqual(gotData, tt.wantData) {
					t.Errorf("parseLogMsg() = %v, want %v", gotData, tt.wantData)
				}
			})
		}

	*/
}
