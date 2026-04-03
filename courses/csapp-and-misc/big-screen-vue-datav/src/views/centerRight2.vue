<template>
  <div id="centreRight2">
    <div class="bg-color-black">
      <div class="d-flex pt-2 pl-2">
        <span style="color:#5cd9e8">
          <icon name="align-left"></icon>
        </span>
        <span class="fs-xl text mx-2">没想好写啥</span>
      </div>
      <div class="d-flex jc-center body-box" style=" margin-top: 0;">
        <dv-capsule-chart :config="config" style="width: 100%;height:2rem" />
        <!-- ---------------------------------------- -->
        <centreRight2Chart1 />
      </div>
    </div>
  </div>
</template>

<script>
import centreRight2Chart1 from "@/components/echart/centerRight/centerRightChart";

export default {
  data() {
    return {
      config: {
        data: [
          {
            name: "文科",
            value: 167
          },
          {
            name: "理科",
            value: 67
          },
          {
            name: "工科",
            value: 123
          },
          {
            name: "艺术",
            value: 55
          },
          {
            name: "娱乐",
            value: 98
          }
        ]
      }
    };
  },
  components: { centreRight2Chart1 },
  mounted() {},
  methods: {}
};
</script>

<style lang="scss">
#centreRight2 {
  padding: 0.0625rem;
  height: 5rem;
  min-width: 3.75rem;
  border-radius: 0.0625rem;
  .bg-color-black {
    padding: 0.0625rem;
    height: 5.0625rem;
    border-radius: 0.125rem;
  }
  .text {
    color: #c3cbde;
  }
  .body-box {
    border-radius: 0.125rem;
    overflow: hidden;
  }
}
</style>