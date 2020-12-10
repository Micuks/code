<template>
  <div>
    <Chart :cdata="cdata" />
  </div>
</template>

<script>
import Chart from './chart.vue';
export default {
  data () {
    return {
      cdata: {
        angleAxisData: [
          "文科",
          "理科",
          "工科",
          "艺术",
          "艺术",
          "娱乐",
        ],
        seriesData: [
          {
            value: 87,
            itemStyle: {
              normal: {
                color: "#ff69b4"
              }
            }
          },
          {
            value: 80,
            itemStyle: {
              normal: {
                color: "#9400d3"
              }
            }
          },
          {
            value: 75,
            itemStyle: {
              normal: {
                color: "#7b68ee"
              }
            }
          },
          {
            value: 69,
            itemStyle: {
              normal: {
                color: "#000080"
              }
            }
          },
          {
            value: 63,
            itemStyle: {
              normal: {
                color: "#5f9ea0"
              }
            }
          },
          {
            value: 54,
            itemStyle: {
              normal: {
                color: "#3cb371"
              }
            }
          },
        ]
      }
    }
  },
  components: {
    Chart,
  },
  mounted () {
  },
  methods: {
  }
}
</script>

<style lang="scss" scoped>
</style>