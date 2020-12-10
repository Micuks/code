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
        xData: ["数学", "程序", "物理", "哲学", "经济", "法律","体育","政治"],
        seriesData: [
          { value: 10, name: "数学" },
          { value: 5, name: "程序" },
          { value: 15, name: "物理" },
          { value: 25, name: "哲学" },
          { value: 20, name: "经济" },
          { value: 35, name: "法律" },
          { value: 20, name: "体育" },
          { value: 20, name: "政治" },
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