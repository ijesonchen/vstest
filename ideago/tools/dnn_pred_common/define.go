package dnn_pred_common

import "time"

type CheckPointV1 struct {
	Id    []uint64  `json:"id"`
	Len   []int     `json:"len"`
	Rid   string    `json:"r_id"`
	Iid   int64     `json:"iid"`
	Score float32   `json:"score"`
	Embed []float32 `json:"embed"`
}

type CheckPoint struct {
	Id    []uint64  `json:"id"`
	Len   []int     `json:"len"`
	Rid   string    `json:"r_id"`
	Iid   int64     `json:"iid"`
	Score float32   `json:"score"`
	Embed []float32 `json:"embed"`
}

type ReqData struct {
	Rid       string
	Uid       string
	UserFea   string
	ItemIds   []int64 // used for check
	ItemFea   map[int64]string
	IidIdxMap map[int64]int // item id -> index of ItemFea/ItemIds
}

type dnnData struct {
	embed []float32
	score float32
	req   string
	doc   string
}

type logData struct {
	Level   string
	Time    time.Time
	Message string
}

const (
	zeroTypeInvalid = iota
	zeroTypeReq
	zeroTypeUser
	zeroTypeItem
	zeroTypeScore
)

var (
	zeroTypeMap = map[string]int{
		"check_point_req":   zeroTypeReq,
		"check_point_user":  zeroTypeUser,
		"check_point_item":  zeroTypeItem,
		"check_point_score": zeroTypeScore,
	}
)
