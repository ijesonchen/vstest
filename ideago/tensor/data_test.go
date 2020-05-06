package main

import (
	"reflect"
	"testing"
)

func Test_parseLogMsg(t *testing.T) {
	msg := "check_point_score: 111111111 2367092 0.001332 [0.03977116,0.0076476964]"
	data, ok := parseLogMsg(msg)
	if !ok {
		t.Errorf("parseLogMsg() return false")
	}
	want := dnnData{
		input: []float32{0.03977116, 0.0076476964},
		score: 0.001332,
		req:   "111111111",
		doc:   "2367092",
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
