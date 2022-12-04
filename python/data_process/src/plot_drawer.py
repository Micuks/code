from matplotlib import pyplot as plt
import seaborn as sns


class plot_drawer:
    def __init__(self, data):
        self.data = data
        # Customize colors.
        self._customize_colors()
        # Curtomize plot.
        self._customize_plot()
        # Set default Chinese font.
        self._add_zh_cn_support()

    def _add_zh_cn_support(self):
        # Set default Chinese font.
        plt.rcParams["font.sans-serif"] = ["Songti SC"]
        plt.rcParams["axes.unicode_minus"] = False

    def _customize_colors(self):
        # Customize colors.
        CB91_Blue = "#2CBDFE"
        CB91_Green = "#47DBCD"
        CB91_Pink = "#F3A0F2"
        CB91_Purple = "#9D2EC5"
        CB91_Violet = "#661D98"
        CB91_Amber = "#F5B14C"
        color_list = [
            CB91_Blue,
            CB91_Pink,
            CB91_Green,
            CB91_Amber,
            CB91_Purple,
            CB91_Violet,
        ]
        plt.rcParams["axes.prop_cycle"] = plt.cycler(color=color_list)
        self.colors = color_list

    def _customize_plot(self):
        sns.set(
            font=["Songti SC", "Franklin Gothic Book"],
            rc={
                "axes.axisbelow": False,
                "axes.edgecolor": "lightgrey",
                "axes.facecolor": "white",
                "axes.grid": True,
                "axes.labelcolor": "dimgrey",
                "axes.spines.right": False,
                "axes.spines.top": False,
                "figure.facecolor": "white",
                "lines.solid_capstyle": "round",
                "patch.edgecolor": "w",
                "patch.force_edgecolor": True,
                "text.color": "dimgrey",
                "xtick.bottom": False,
                "xtick.color": "dimgrey",
                "xtick.direction": "out",
                "xtick.top": False,
                "ytick.color": "dimgrey",
                "ytick.direction": "out",
                "ytick.left": False,
                "ytick.right": False,
            },
        )
        sns.set_context(
            "notebook", rc={"font.size": 16, "axes.titlesize": 20,
                            "axes.labelsize": 15}
        )

    def draw_price_scatter_plot(self):
        avg_price = list()
        tot_price = list()
        resblock_type = list()
        # Get unqiue types in resblock_type.
        types = list()

        # Collect data.
        for d in self.data:
            avg_price.append(d["均价"])
            tot_price.append(d["总价"])
            resblock_type.append(d["类型"])

        def get_label(item: str):
            # If label[item] already exists, do not add new one.
            if item in types:
                return ""
            else:
                # Else add new one.
                types.append(item)
                return item

        def get_color(item: str):
            """
            If resblock_type item already exists, return the corresponding
            color.
            """

            def color(item: str):
                clrs = self.colors
                idx = types.index(item)
                return clrs[idx % len(clrs)]

            if item in types:
                return color(item)
            else:
                return self.colors[0]

        # Draw data on plot.
        for i in range(len(tot_price)):
            rtype = resblock_type[i]
            plt.scatter(
                tot_price[i],
                avg_price[i],
                label=get_label(rtype),
                s=35,
                c=get_color(rtype),
            )

        print(types)

        # Add axe labels and caption.
        plt.title("楼盘价格分布散点图")
        plt.xlabel("总价(万元)")
        plt.ylabel("均价(元)")
        plt.grid(True, linestyle="--", c="dimgrey", alpha=0.8)
        plt.legend(loc="lower right")

        plt.show()
