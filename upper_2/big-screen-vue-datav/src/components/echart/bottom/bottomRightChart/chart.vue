<template>
  <div>
    <Echart
      :options="options"
      id="centreLeft1Chart"
      height="6rem"
      width="100%"
    ></Echart>
  </div>
</template>

<script>
import Echart from '@/common/echart'
export default {
  data () {
    return {
      options: {},
      // 定义颜色
      colorList: {
        linearYtoG: {
          type: "linear",
          x: 0,
          y: 0,
          x2: 1,
          y2: 1,
          colorStops: [
            {
              offset: 0,
              color: "#00ced1"
            },
            {
              offset: 1,
              color: "#006400"
            }
          ]
        },
        linearGtoB: {
          type: "linear",
          x: 0,
          y: 0,
          x2: 1,
          y2: 0,
          colorStops: [
            {
              offset: 0,
              color: "#daa520"
            },
            {
              offset: 1,
              color: "#ffa500"
            }
          ]
        },
        linearBtoG: {
          type: "linear",
          x: 0,
          y: 0,
          x2: 1,
          y2: 0,
          colorStops: [
            {
              offset: 0,
              color: "#1c98e8"
            },
            {
              offset: 1,
              color: "#28f8de"
            }
          ]
        },
        areaBtoG: {
          type: "linear",
          x: 0,
          y: 0,
          x2: 0,
          y2: 1,
          colorStops: [
            {
              offset: 0,
              color: "rgba(35,184,210,.2)"
            },
            {
              offset: 1,
              color: "rgba(35,184,210,0)"
            }
          ]
        }
      }
    };
  },
  components: {
    Echart,
  },
  props: {
    cdata: {
      type: Object,
      default: () => ({})
    },
  },
  watch: {
    cdata: {
      handler (newData) {
        this.options = {
          title: {
            text: "",
            textStyle: {
              color: "#D3D6DD",
              fontSize: 24,
              fontWeight: "normal"
            },
            subtext: newData.year + "/" + newData.weekCategory[6],
            subtextStyle: {
              color: "#fff",
              fontSize: 16
            },
            top: 50,
            left: 80
          },
          legend: {
            top: 120,
            left: 80,
            orient: "vertical",
            itemGap: 15,
            itemWidth: 12,
            itemHeight: 12,
            data: ["平均评价", "本周评价"],
            textStyle: {
              color: "#fff",
              fontSize: 14
            }
          },
          tooltip: {
            trigger: "item"
          },
          radar: {
            center: ["68%", "27%"],
            radius: "40%",
            name: {
              color: "#fff"
            },
            splitNumber: 8,
            axisLine: {
              lineStyle: {
                color: this.colorList.linearYtoG,
                opacity: 0.6
              }
            },
            splitLine: {
              lineStyle: {
                color: this.colorList.linearYtoG,
                opacity: 0.6
              }
            },
            splitArea: {
              areaStyle: {
                color: "#fff",
                opacity: 0.1,
                shadowBlur: 25,
                shadowColor: "#000",
                shadowOffsetX: 0,
                shadowOffsetY: 5
              }
            },
            indicator: [
              {
                name: "自习环境",
                max: newData.maxData
              },
              {
                name: "藏书质量",
                max: 10
              },
              {
                name: "借还体验",
                max: 12
              },
              {
                name: "预约体验",
                max: 3.5
              }
            ]
          },
          grid: {
            left: 90,
            right: 80,
            bottom: 40,
            top: "60%"
          },
          xAxis: {
            type: "category",
            position: "bottom",
            axisLine: true,
            axisLabel: {
              color: "rgba(255,255,255,.8)",
              fontSize: 12
            },
            data: newData.weekCategory
          },
          // 下方Y轴
          yAxis: {
            name: "到馆人数",
            nameLocation: "end",
            nameGap: 24,
            nameTextStyle: {
              color: "rgba(255,255,255,.5)",
              fontSize: 14
            },
            max: newData.maxData,
            splitNumber: 4,

            axisLine: {
              lineStyle: {
                opacity: 0
              }
            },
            splitLine: {
              show: true,
              lineStyle: {
                color: "#fff",
                opacity: 0.1
              }
            },
            axisLabel: {
              color: "rgba(255,255,255,.8)",
              fontSize: 12
            }
          },
          series: [
            {
              name: "",
              type: "radar",
              symbolSize: 0,
              data: [
                {
                  value: newData.radarDataAvg[6],
                  name: "平均评价",
                  itemStyle: {
                    normal: {
                      color: "#daa520"
                    }
                  },
                  lineStyle: {
                    normal: {
                      opacity: 0
                    }
                  },
                  areaStyle: {
                    normal: {
                      color: "#daa520",
                      shadowBlur: 25,
                      shadowColor: "rgba(248,211,81,.3)",
                      shadowOffsetX: 0,
                      shadowOffsetY: -10,
                      opacity: 1
                    }
                  }
                },
                {
                  value: newData.radarData[6],
                  name: "本周评价",
                  itemStyle: {
                    normal: {
                      color: "#43dfa2"
                    }
                  },
                  lineStyle: {
                    normal: {
                      opacity: 0
                    }
                  },
                  areaStyle: {
                    normal: {
                      // color: this.colorList.linearGtoB,
                      color:"#43dfa2",
                      shadowBlur: 15,
                      shadowColor: "rgba(0,0,0,.2)",
                      shadowOffsetX: 0,
                      shadowOffsetY: 5,
                      opacity: 0.8
                    }
                  }
                }
              ]
            },
            {
              name: "",
              type: "line",
              smooth: true,
              symbol: "emptyCircle",
              symbolSize: 8,
              itemStyle: {
                normal: {
                  color: "#fff"
                }
              },
              lineStyle: {
                normal: {
                  color: this.colorList.linearBtoG,
                  width: 3
                }
              },
              areaStyle: {
                normal: {
                  color: this.colorList.areaBtoG
                }
              },
              data: newData.weekLineData,
              lineSmooth: true,
              markLine: {
                silent: true,
                data: [
                  {
                    type: "average",
                    name: "平均值"
                  }
                ],
                precision: 0,
                label: {
                  normal: {
                    formatter: "平均值: \n {c}"
                  }
                },
                lineStyle: {
                  normal: {
                    color: "rgba(248,211,81,.7)"
                  }
                }
              },
              tooltip: {
                position: "top",
                formatter: "{c} m",
                backgroundColor: "rgba(28,152,232,.2)",
                padding: 6
              }
            },
            {
              name: "占位背景",
              type: "bar",
              itemStyle: {
                normal: {
                  show: true,
                  color: "#000",
                  opacity: 0
                }
              },
              silent: true,
              barWidth: "50%",
              data: newData.weekMaxData,
              animation: false
            }
          ]
        }
      },
      immediate: true,
      deep: true
    }
  }
};
</script>

<style lang="scss" scoped>
</style>