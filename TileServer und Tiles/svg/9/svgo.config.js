// 'removeOffCanvasPaths'
module.exports = {
  multipass: false, // boolean. false by default
  js2svg: {
    indent: 2, // string with spaces or number of spaces. 4 by default
    pretty: true, // boolean, false by default
  },
  plugins: [
    {
      name: "cleanupAttrs",
      params: {
        trim: false,
      },
    },
    "mergeStyles", ///////////////////////
    "inlineStyles",
    "removeDoctype",
    "removeXMLProcInst",
    "removeComments",
    "removeMetadata",
    "removeTitle",
    "removeDesc",
    "removeUselessDefs", ///////////////////////
    "removeEditorsNSData",
    "removeEmptyAttrs",
    "removeHiddenElems",
    "removeEmptyContainers",
    "removeViewBox",
    "cleanupEnableBackground",
    {
      name: "minifyStyles",
      params: {
        usage: {
          force: true,
          ids: true,
          classes: true,
          tags: true,
        },
      },
    },
    // {//remove trasform
    //   name: "convertStyleToAttrs",
    //   params: {
    //     usage: {
    //       keepImportant: true,
    //     },
    //   },
    // },
    {
      name: "convertColors",
      params: {
        usage: {
          currentColor: true,
          names2hex: true,
          rgb2hex: true,
          shorthex: true,
          shortname: true,
        },
      },
    },
    {
      name: "convertPathData",
      params: {
        applyTransforms: false,
        applyTransformsStroked: false,
        noSpaceAfterFlags: true,
        makeArcs: {
          threshold: 0.5, // coefficient of rounding error
          tolerance: 0.1, // percentage of radius
        },
        straightCurves: true,
        lineShorthands: true,
        curveSmoothShorthands: true,
        floatPrecision: 1,
        transformPrecision: 1,
        // removeUseless: true,
        collapseRepeated: true,
        utilizeAbsolute: true,
        leadingZero: true,
        negativeExtraSpace: false,
        noSpaceAfterFlags: true, // a20 60 45 0 1 30 20 → a20 60 45 0130 20
        forceAbsolutePath: true,
      },
    },
    // {
    //   name: "convertTransform",
    //   params: {
    //     convertToShorts: true,
    //     degPrecision: 1, // transformPrecision (or matrix precision) - 2 by default
    //     floatPrecision: 1,
    //     transformPrecision: 0,
    //     matrixToTransform: true,
    //     shortTranslate: true,
    //     shortScale: true,
    //     shortRotate: true,
    //     removeUseless: true,
    //     collapseIntoOne: true,
    //     leadingZero: true,
    //     negativeExtraSpace: false,
    //   },
    // },
    {
      name: "removeUnknownsAndDefaults",
      params: {
        unknownContent: true,
        unknownAttrs: true,
        defaultAttrs: true,
        uselessOverrides: true,
        keepDataAttrs: false,
        keepAriaAttrs: false,
        keepRoleAttr: false,
      },
    },
    "removeNonInheritableGroupAttrs",
    {
      name: "removeUselessStrokeAndFill",
      params: {
        stroke: true,
        fill: true,
      },
    },
    "removeUnusedNS",
    {
      name: "cleanupIDs",
      params: {
        remove: true,
        minify: true,
        prefix: "",
        preserve: [],
        preservePrefixes: [],
        force: true,
      },
    },
    // 'prefixIds',
    {
      name: "cleanupNumericValues",
      params: {
        floatPrecision: 1,
        leadingZero: true,
        defaultPx: true,
        convertToPx: true,
      },
    },
    {
      name: "cleanupListOfValues",
      params: {
        floatPrecision: 1,
        leadingZero: true,
        defaultPx: true,
        convertToPx: true,
      },
    },
    "moveElemsAttrsToGroup",
    "moveGroupAttrsToElems",
    "collapseGroups",
    // "removeRasterImages",
    {
      name: "mergePaths",
      params: {
        floatPrecision: 1,
        force: true,
        noSpaceAfterFlags: true,
      },
    },
    "convertShapeToPath",
    "convertPathData",
    {
      name: "convertEllipseToCircle",
      params: {
        floatPrecision: 1,
        convertArcs: true,
      },
    },
    "sortAttrs",
    "sortDefsChildren", //////
    "removeDimensions",
    "removeAttrs",
    // "removeElementsByAttr",
    // "removeOffCanvasPaths",
    "removeStyleElement",
    "removeScriptElement",
    "reusePaths",
  ],
};
