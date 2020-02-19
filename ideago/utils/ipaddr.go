package utils

import (
	"log"
	"net"
)

type IpAddr struct {
	V4Hex uint32
	V4    net.IP
	V6    net.IP
}

func (addr *IpAddr) IsValid() bool {
	if len(addr.V4) == net.IPv4len || len(addr.V6) == net.IPv6len {
		return true
	}
	return false
}

// 返回ip地址，过滤未启用、回环、点对点地址
func GetIpAddr() (ipAddrs []IpAddr, err error) {
	ips, err := net.Interfaces()
	if err != nil {
		return
	}
	log.Println(err)

	var ipaddr IpAddr
	for i, ip := range ips {
		if (ip.Flags & net.FlagUp) == 0 {
			continue
		}
		if (ip.Flags&net.FlagLoopback) != 0 ||
			(ip.Flags&net.FlagPointToPoint) != 0 {
			continue
		}
		addrs, err := ip.Addrs()
		if err != nil {
			log.Println("ip.Addrs error,", err)
			continue
		}
		log.Printf("%+v %+v %v\n", ip, addrs, err)
		for _, addr := range addrs {
			if ip, ok := addr.(*net.IPNet); ok {
				if len(ip.IP) == net.IPv6len && ip.IP[0] != 0 {
					ipaddr.V6 = CopySliceByte(ip.IP.To16())
				}
				if ip4 := ip.IP.To4(); len(ip4) == net.IPv4len {
					ipaddr.V4 = CopySliceByte(ip4)
					ipaddr.V4Hex = uint32(ip4[0])<<24 | uint32(ip4[1])<<16 | uint32(ip4[2])<<8 | uint32(ip4[3])
				}
			}
		}
		log.Printf("got ipaddr %d %+v %x %+v", i, ip, ipaddr.V4Hex, ipaddr)
		if ipaddr.IsValid() {
			ipAddrs = append(ipAddrs, ipaddr)
		}
	}

	return
}
