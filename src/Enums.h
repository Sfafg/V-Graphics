#pragma once

namespace vg
{
    enum class PresentMode
    {
        Immediate = 0,
        Mailbox = 1,
        Fifo = 2,
        FifoRelaxed = 3,
        SharedDemandRefresh = 1000111000,
        SharedContinuousRefresh = 1000111001,
    };
    enum class CompositeAlpha
    {
        Opaque = 0x00000001,
        PreMultiplied = 0x00000002,
        PostMultiplied = 0x00000004,
        Inherit = 0x00000008
    };
    enum class Usage
    {
        TransferSrc = 0x00000001,
        TransferDst = 0x00000002,
        Sampled = 0x00000004,
        Storage = 0x00000008,
        ColorAttachment = 0x00000010,
        DepthStencilAttachment = 0x00000020,
        TransientAttachment = 0x00000040,
        InputAttachment = 0x00000080,
        VideoDecodeDst = 0x00000400,
        VideoDecodeSrc = 0x00000800,
        VideoDecodeDpb = 0x00001000,
        FragmentDensityMap = 0x00000200,
        FragmentShadingRateAttachment = 0x00000100,
        HostTransfer = 0x00400000,
        VideoEncodeDst = 0x00002000,
        VideoEncodeSrc = 0x00004000,
        VideoEncodeDpb = 0x00008000,
        AttachmentFeedbackLoop = 0x00080000,
        InvocationMask = 0x00040000,
        SampleWeight = 0x00100000,
        SampleBlockMatch = 0x00200000,
    };
    enum class Format
    {
        Undefined = 0,
        R4G4UNORMPACK8 = 1,
        R4G4B4A4UNORMPACK16 = 2,
        B4G4R4A4UNORMPACK16 = 3,
        R5G6B5UNORMPACK16 = 4,
        B5G6R5UNORMPACK16 = 5,
        R5G5B5A1UNORMPACK16 = 6,
        B5G5R5A1UNORMPACK16 = 7,
        A1R5G5B5UNORMPACK16 = 8,
        R8UNORM = 9,
        R8SNORM = 10,
        R8USCALED = 11,
        R8SSCALED = 12,
        R8UINT = 13,
        R8SINT = 14,
        R8SRGB = 15,
        R8G8UNORM = 16,
        R8G8SNORM = 17,
        R8G8USCALED = 18,
        R8G8SSCALED = 19,
        R8G8UINT = 20,
        R8G8SINT = 21,
        R8G8SRGB = 22,
        R8G8B8UNORM = 23,
        R8G8B8SNORM = 24,
        R8G8B8USCALED = 25,
        R8G8B8SSCALED = 26,
        R8G8B8UINT = 27,
        R8G8B8SINT = 28,
        R8G8B8SRGB = 29,
        B8G8R8UNORM = 30,
        B8G8R8SNORM = 31,
        B8G8R8USCALED = 32,
        B8G8R8SSCALED = 33,
        B8G8R8UINT = 34,
        B8G8R8SINT = 35,
        B8G8R8SRGB = 36,
        R8G8B8A8UNORM = 37,
        R8G8B8A8SNORM = 38,
        R8G8B8A8USCALED = 39,
        R8G8B8A8SSCALED = 40,
        R8G8B8A8UINT = 41,
        R8G8B8A8SINT = 42,
        R8G8B8A8SRGB = 43,
        B8G8R8A8UNORM = 44,
        B8G8R8A8SNORM = 45,
        B8G8R8A8USCALED = 46,
        B8G8R8A8SSCALED = 47,
        B8G8R8A8UINT = 48,
        B8G8R8A8SINT = 49,
        B8G8R8A8SRGB = 50,
        A8B8G8R8UNORMPACK32 = 51,
        A8B8G8R8SNORMPACK32 = 52,
        A8B8G8R8USCALEDPACK32 = 53,
        A8B8G8R8SSCALEDPACK32 = 54,
        A8B8G8R8UINTPACK32 = 55,
        A8B8G8R8SINTPACK32 = 56,
        A8B8G8R8SRGBPACK32 = 57,
        A2R10G10B10UNORMPACK32 = 58,
        A2R10G10B10SNORMPACK32 = 59,
        A2R10G10B10USCALEDPACK32 = 60,
        A2R10G10B10SSCALEDPACK32 = 61,
        A2R10G10B10UINTPACK32 = 62,
        A2R10G10B10SINTPACK32 = 63,
        A2B10G10R10UNORMPACK32 = 64,
        A2B10G10R10SNORMPACK32 = 65,
        A2B10G10R10USCALEDPACK32 = 66,
        A2B10G10R10SSCALEDPACK32 = 67,
        A2B10G10R10UINTPACK32 = 68,
        A2B10G10R10SINTPACK32 = 69,
        R16UNORM = 70,
        R16SNORM = 71,
        R16USCALED = 72,
        R16SSCALED = 73,
        R16UINT = 74,
        R16SINT = 75,
        R16SFLOAT = 76,
        R16G16UNORM = 77,
        R16G16SNORM = 78,
        R16G16USCALED = 79,
        R16G16SSCALED = 80,
        R16G16UINT = 81,
        R16G16SINT = 82,
        R16G16SFLOAT = 83,
        R16G16B16UNORM = 84,
        R16G16B16SNORM = 85,
        R16G16B16USCALED = 86,
        R16G16B16SSCALED = 87,
        R16G16B16UINT = 88,
        R16G16B16SINT = 89,
        R16G16B16SFLOAT = 90,
        R16G16B16A16UNORM = 91,
        R16G16B16A16SNORM = 92,
        R16G16B16A16USCALED = 93,
        R16G16B16A16SSCALED = 94,
        R16G16B16A16UINT = 95,
        R16G16B16A16SINT = 96,
        R16G16B16A16SFLOAT = 97,
        R32UINT = 98,
        R32SINT = 99,
        R32SFLOAT = 100,
        R32G32UINT = 101,
        R32G32SINT = 102,
        R32G32SFLOAT = 103,
        R32G32B32UINT = 104,
        R32G32B32SINT = 105,
        R32G32B32SFLOAT = 106,
        R32G32B32A32UINT = 107,
        R32G32B32A32SINT = 108,
        R32G32B32A32SFLOAT = 109,
        R64UINT = 110,
        R64SINT = 111,
        R64SFLOAT = 112,
        R64G64UINT = 113,
        R64G64SINT = 114,
        R64G64SFLOAT = 115,
        R64G64B64UINT = 116,
        R64G64B64SINT = 117,
        R64G64B64SFLOAT = 118,
        R64G64B64A64UINT = 119,
        R64G64B64A64SINT = 120,
        R64G64B64A64SFLOAT = 121,
        B10G11R11UFLOATPACK32 = 122,
        E5B9G9R9UFLOATPACK32 = 123,
        D16UNORM = 124,
        X8D24UNORMPACK32 = 125,
        D32SFLOAT = 126,
        S8UINT = 127,
        D16UNORMS8UINT = 128,
        D24UNORMS8UINT = 129,
        D32SFLOATS8UINT = 130,
        BC1RGBUNORMBLOCK = 131,
        BC1RGBSRGBBLOCK = 132,
        BC1RGBAUNORMBLOCK = 133,
        BC1RGBASRGBBLOCK = 134,
        BC2UNORMBLOCK = 135,
        BC2SRGBBLOCK = 136,
        BC3UNORMBLOCK = 137,
        BC3SRGBBLOCK = 138,
        BC4UNORMBLOCK = 139,
        BC4SNORMBLOCK = 140,
        BC5UNORMBLOCK = 141,
        BC5SNORMBLOCK = 142,
        BC6HUFLOATBLOCK = 143,
        BC6HSFLOATBLOCK = 144,
        BC7UNORMBLOCK = 145,
        BC7SRGBBLOCK = 146,
        ETC2R8G8B8UNORMBLOCK = 147,
        ETC2R8G8B8SRGBBLOCK = 148,
        ETC2R8G8B8A1UNORMBLOCK = 149,
        ETC2R8G8B8A1SRGBBLOCK = 150,
        ETC2R8G8B8A8UNORMBLOCK = 151,
        ETC2R8G8B8A8SRGBBLOCK = 152,
        EACR11UNORMBLOCK = 153,
        EACR11SNORMBLOCK = 154,
        EACR11G11UNORMBLOCK = 155,
        EACR11G11SNORMBLOCK = 156,
        ASTC4x4UNORMBLOCK = 157,
        ASTC4x4SRGBBLOCK = 158,
        ASTC5x4UNORMBLOCK = 159,
        ASTC5x4SRGBBLOCK = 160,
        ASTC5x5UNORMBLOCK = 161,
        ASTC5x5SRGBBLOCK = 162,
        ASTC6x5UNORMBLOCK = 163,
        ASTC6x5SRGBBLOCK = 164,
        ASTC6x6UNORMBLOCK = 165,
        ASTC6x6SRGBBLOCK = 166,
        ASTC8x5UNORMBLOCK = 167,
        ASTC8x5SRGBBLOCK = 168,
        ASTC8x6UNORMBLOCK = 169,
        ASTC8x6SRGBBLOCK = 170,
        ASTC8x8UNORMBLOCK = 171,
        ASTC8x8SRGBBLOCK = 172,
        ASTC10x5UNORMBLOCK = 173,
        ASTC10x5SRGBBLOCK = 174,
        ASTC10x6UNORMBLOCK = 175,
        ASTC10x6SRGBBLOCK = 176,
        ASTC10x8UNORMBLOCK = 177,
        ASTC10x8SRGBBLOCK = 178,
        ASTC10x10UNORMBLOCK = 179,
        ASTC10x10SRGBBLOCK = 180,
        ASTC12x10UNORMBLOCK = 181,
        ASTC12x10SRGBBLOCK = 182,
        ASTC12x12UNORMBLOCK = 183,
        ASTC12x12SRGBBLOCK = 184,
        G8B8G8R8422UNORM = 1000156000,
        B8G8R8G8422UNORM = 1000156001,
        G8B8R83PLANE420UNORM = 1000156002,
        G8B8R82PLANE420UNORM = 1000156003,
        G8B8R83PLANE422UNORM = 1000156004,
        G8B8R82PLANE422UNORM = 1000156005,
        G8B8R83PLANE444UNORM = 1000156006,
        R10X6UNORMPACK16 = 1000156007,
        R10X6G10X6UNORM2PACK16 = 1000156008,
        R10X6G10X6B10X6A10X6UNORM4PACK16 = 1000156009,
        G10X6B10X6G10X6R10X6422UNORM4PACK16 = 1000156010,
        B10X6G10X6R10X6G10X6422UNORM4PACK16 = 1000156011,
        G10X6B10X6R10X63PLANE420UNORM3PACK16 = 1000156012,
        G10X6B10X6R10X62PLANE420UNORM3PACK16 = 1000156013,
        G10X6B10X6R10X63PLANE422UNORM3PACK16 = 1000156014,
        G10X6B10X6R10X62PLANE422UNORM3PACK16 = 1000156015,
        G10X6B10X6R10X63PLANE444UNORM3PACK16 = 1000156016,
        R12X4UNORMPACK16 = 1000156017,
        R12X4G12X4UNORM2PACK16 = 1000156018,
        R12X4G12X4B12X4A12X4UNORM4PACK16 = 1000156019,
        G12X4B12X4G12X4R12X4422UNORM4PACK16 = 1000156020,
        B12X4G12X4R12X4G12X4422UNORM4PACK16 = 1000156021,
        G12X4B12X4R12X43PLANE420UNORM3PACK16 = 1000156022,
        G12X4B12X4R12X42PLANE420UNORM3PACK16 = 1000156023,
        G12X4B12X4R12X43PLANE422UNORM3PACK16 = 1000156024,
        G12X4B12X4R12X42PLANE422UNORM3PACK16 = 1000156025,
        G12X4B12X4R12X43PLANE444UNORM3PACK16 = 1000156026,
        G16B16G16R16422UNORM = 1000156027,
        B16G16R16G16422UNORM = 1000156028,
        G16B16R163PLANE420UNORM = 1000156029,
        G16B16R162PLANE420UNORM = 1000156030,
        G16B16R163PLANE422UNORM = 1000156031,
        G16B16R162PLANE422UNORM = 1000156032,
        G16B16R163PLANE444UNORM = 1000156033,
        G8B8R82PLANE444UNORM = 1000330000,
        G10X6B10X6R10X62PLANE444UNORM3PACK16 = 1000330001,
        G12X4B12X4R12X42PLANE444UNORM3PACK16 = 1000330002,
        G16B16R162PLANE444UNORM = 1000330003,
        A4R4G4B4UNORMPACK16 = 1000340000,
        A4B4G4R4UNORMPACK16 = 1000340001,
        ASTC4x4SFLOATBLOCK = 1000066000,
        ASTC5x4SFLOATBLOCK = 1000066001,
        ASTC5x5SFLOATBLOCK = 1000066002,
        ASTC6x5SFLOATBLOCK = 1000066003,
        ASTC6x6SFLOATBLOCK = 1000066004,
        ASTC8x5SFLOATBLOCK = 1000066005,
        ASTC8x6SFLOATBLOCK = 1000066006,
        ASTC8x8SFLOATBLOCK = 1000066007,
        ASTC10x5SFLOATBLOCK = 1000066008,
        ASTC10x6SFLOATBLOCK = 1000066009,
        ASTC10x8SFLOATBLOCK = 1000066010,
        ASTC10x10SFLOATBLOCK = 1000066011,
        ASTC12x10SFLOATBLOCK = 1000066012,
        ASTC12x12SFLOATBLOCK = 1000066013,
        PVRTC12BPPUNORMBLOCKIMG = 1000054000,
        PVRTC14BPPUNORMBLOCKIMG = 1000054001,
        PVRTC22BPPUNORMBLOCKIMG = 1000054002,
        PVRTC24BPPUNORMBLOCKIMG = 1000054003,
        PVRTC12BPPSRGBBLOCKIMG = 1000054004,
        PVRTC14BPPSRGBBLOCKIMG = 1000054005,
        PVRTC22BPPSRGBBLOCKIMG = 1000054006,
        PVRTC24BPPSRGBBLOCKIMG = 1000054007,
        R16G16S105 = 1000464000,
        A1B5G5R5UNORMPACK16 = 1000470000,
        A8UNORM = 1000470001,
    };
    enum class ColorSpace
    {
        SRGBNL = 0,
        DispP3NL = 1000104002,
        ExtSRGBL = 1000104003,
        DispP3L = 1000104004,
        DciP3NL = 1000104005,
        Bt709L = 1000104006,
        Bt709NL = 1000104007,
        Bt2020L = 1000104008,
        HDR10St2084 = 1000104009,
        Dolbyvision = 1000104010,
        HDR10HLG = 1000104011,
        AdobeRGBL = 1000104012,
        AdobeRGBNL = 1000104013,
        PassThrough = 1000104014,
        ExtSRGBNL = 1000213000
    };
    enum class ShaderStage
    {
        Vertex = 0x00000001,
        TessellationControl = 0x00000002,
        TessellationEvaluation = 0x00000004,
        Geometry = 0x00000008,
        Fragment = 0x00000010,
        Compute = 0x00000020,
        AllGraphics = 0x0000001F,
        All = 0x7FFFFFFF,
        Raygen = 0x00000100,
        AnyHit = 0x00000200,
        ClosestHit = 0x00000400,
        Miss = 0x00000800,
        Intersection = 0x00001000,
        Callable = 0x00002000,
        Task = 0x00000040,
        Mesh = 0x00000080,
        SubpassShading = 0x00004000,
        ClusterCulling = 0x00080000,
    };
    enum class DynamicState
    {
        Viewport = 0,
        Scissor = 1,
        LineWidth = 2,
        DepthBias = 3,
        BlendConstants = 4,
        DepthBounds = 5,
        StencilCompareMask = 6,
        StencilWriteMask = 7,
        StencilReference = 8,
        CullMode = 1000267000,
        FrontFace = 1000267001,
        PrimitiveTopology = 1000267002,
        ViewportWithCount = 1000267003,
        ScissorWithCount = 1000267004,
        VertexInputBindingStride = 1000267005,
        DepthTestEnable = 1000267006,
        DepthWriteEnable = 1000267007,
        DepthCompareOp = 1000267008,
        DepthBoundsTestEnable = 1000267009,
        StencilTestEnable = 1000267010,
        StencilOp = 1000267011,
        RasterizerDiscardEnable = 1000377001,
        DepthBiasEnable = 1000377002,
        PrimitiveRestartEnable = 1000377004,
        ViewportWScaling = 1000087000,
        DiscardRectangle = 1000099000,
        DiscardRectangleEnable = 1000099001,
        DiscardRectangleMode = 1000099002,
        SampleLocations = 1000143000,
        RayTracingPipelineStackSize = 1000347000,
        ViewportShadingRatePalette = 1000164004,
        ViewportCoarseSampleOrder = 1000164006,
        ExclusiveScissorEnable = 1000205000,
        ExclusiveScissor = 1000205001,
        FragmentShadingRate = 1000226000,
        LineStipple = 1000259000,
        VertexInput = 1000352000,
        PatchControlPoints = 1000377000,
        LogicOp = 1000377003,
        ColorWriteEnable = 1000381000,
        TessellationDomainOrigin = 1000455002,
        DepthClampEnable = 1000455003,
        PolygonMode = 1000455004,
        RasterizationSamples = 1000455005,
        SampleMask = 1000455006,
        AlphaToCoverageEnable = 1000455007,
        AlphaToOneEnable = 1000455008,
        LogicOpEnable = 1000455009,
        ColorBlendEnable = 1000455010,
        ColorBlendEquation = 1000455011,
        ColorWriteMask = 1000455012,
        RasterizationStream = 1000455013,
        ConservativeRasterizationMode = 1000455014,
        raPrimitiveOverestimationSize = 1000455015,
        DepthClipEnable = 1000455016,
        SampleLocationsEnable = 1000455017,
        ColorBlendAdvanced = 1000455018,
        ProvokingVertexMode = 1000455019,
        LineRasterizationMode = 1000455020,
        LineStippleEnable = 1000455021,
        DepthClipNegativeOneToOne = 1000455022,
        ViewportWScalingEnable = 1000455023,
        ViewportSwizzle = 1000455024,
        CoverageToColorEnable = 1000455025,
        CoverageToColorLocation = 1000455026,
        CoverageModulationMode = 1000455027,
        CoverageModulationTableEnable = 1000455028,
        CoverageModulationTable = 1000455029,
        ShadingRateImageEnable = 1000455030,
        RepresentativeFragmentTestEnable = 1000455031,
        CoverageReductionMode = 1000455032,
        AttachmentFeedbackLoopEnable = 1000524000,
    };
    enum class Primitive
    {
        Points = 0,
        Lines = 1,
        LineStrip = 2,
        Triangles = 3,
        TriangleStrip = 4,
        TriangleFan = 5,
        LineListWithAdjacency = 6,
        LineStripWithAdjacency = 7,
        TriangleListWithAdjacency = 8,
        TriangleStripWithAdjacency = 9,
        PatchList = 10,
    };
    enum class PolygonMode
    {
        Fill = 0,
        Line = 1,
        Point = 2,
        FillRectangle = 1000153000
    };
    enum class CullMode
    {
        None = 0,
        Front = 0x00000001,
        Back = 0x00000002,
        FrontAndBack = 0x00000003
    };
    enum class FrontFace
    {
        CounterClockwise = 0,
        Clockwise = 1
    };
    enum class ColorComponent
    {
        R = 0x00000001,
        G = 0x00000002,
        B = 0x00000004,
        A = 0x00000008,
        RGB = R | G | B,
        RGBA = RGB | A,
    };
    enum class BlendOp
    {
        Add = 0,
        Subtract = 1,
        ReverseSubtract = 2,
        Min = 3,
        Max = 4,
        Zero = 1000148000,
        Src = 1000148001,
        Dst = 1000148002,
        SrcOver = 1000148003,
        DstOver = 1000148004,
        SrcIn = 1000148005,
        DstIn = 1000148006,
        SrcOut = 1000148007,
        DstOut = 1000148008,
        SrcAtop = 1000148009,
        DstAtop = 1000148010,
        Xor = 1000148011,
        Multiply = 1000148012,
        Screen = 1000148013,
        Overlay = 1000148014,
        Darken = 1000148015,
        Lighten = 1000148016,
        Colordodge = 1000148017,
        Colorburn = 1000148018,
        Hardlight = 1000148019,
        Softlight = 1000148020,
        Difference = 1000148021,
        Exclusion = 1000148022,
        Invert = 1000148023,
        InvertRgb = 1000148024,
        Lineardodge = 1000148025,
        Linearburn = 1000148026,
        Vividlight = 1000148027,
        Linearlight = 1000148028,
        Pinlight = 1000148029,
        Hardmix = 1000148030,
        HslHue = 1000148031,
        HslSaturation = 1000148032,
        HslColor = 1000148033,
        HslLuminosity = 1000148034,
        Plus = 1000148035,
        PlusClamped = 1000148036,
        PlusClampedAlpha = 1000148037,
        PlusDarker = 1000148038,
        Minus = 1000148039,
        MinusClamped = 1000148040,
        Contrast = 1000148041,
        InvertOvg = 1000148042,
        Red = 1000148043,
        Green = 1000148044,
        Blue = 1000148045
    };
    enum class LogicOp
    {
        Clear = 0,
        And = 1,
        AndReverse = 2,
        Copy = 3,
        AndInverted = 4,
        NoOp = 5,
        Xor = 6,
        Or = 7,
        Nor = 8,
        Equivalent = 9,
        Invert = 10,
        OrReverse = 11,
        CopyInverted = 12,
        OrInverted = 13,
        Nand = 14,
        Set = 15,
    };
    enum class BlendFactor
    {
        Zero = 0,
        One = 1,
        SrcColor = 2,
        OneMinusSrcColor = 3,
        DstColor = 4,
        OneMinusDstColor = 5,
        SrcAlpha = 6,
        OneMinusSrcAlpha = 7,
        DstAlpha = 8,
        OneMinusDstAlpha = 9,
        ConstantColor = 10,
        OneMinusConstantColor = 11,
        ConstantAlpha = 12,
        OneMinusConstantAlpha = 13,
        SrcAlphaSaturate = 14,
        Src1Color = 15,
        OneMinusSrc1Color = 16,
        Src1Alpha = 17,
        OneMinusSrc1Alpha = 18,
    };
    enum class LoadOp
    {
        Load = 0,
        Clear = 1,
        DontCare = 2,
        None = 1000400000
    };
    enum class StoreOp
    {
        Store = 0,
        DontCare = 1,
        None = 1000301000,
    };
    enum class ImageLayout
    {
        Undefined = 0,
        General = 1,
        ColorAttachmentOptimal = 2,
        DepthStencilAttachmentOptimal = 3,
        DepthStencilReadOnlyOptimal = 4,
        ShaderReadOnlyOptimal = 5,
        TransferSrcOptimal = 6,
        TransferDstOptimal = 7,
        Preinitialized = 8,
        DepthReadOnlyStencilAttachmentOptimal = 1000117000,
        DepthAttachmentStencilReadOnlyOptimal = 1000117001,
        DepthAttachmentOptimal = 1000241000,
        DepthReadOnlyOptimal = 1000241001,
        StencilAttachmentOptimal = 1000241002,
        StencilReadOnlyOptimal = 1000241003,
        ReadOnlyOptimal = 1000314000,
        AttachmentOptimal = 1000314001,
        PresentSrc = 1000001002,
        VideoDecodeDst = 1000024000,
        VideoDecodeSrc = 1000024001,
        VideoDecodeDpb = 1000024002,
        SharedPresent = 1000111000,
        FragmentDensityMapOptimal = 1000218000,
        FragmentShadingRateAttachmentOptimal = 1000164003,
        VideoEncodeDst = 1000299000,
        VideoEncodeSrc = 1000299001,
        VideoEncodeDpb = 1000299002,
        AttachmentFeedbackLoopOptimal = 1000339000,
    };
    enum class PipelineStage
    {
        TopOfPipe = 1,
        DrawIndirect = 2,
        VertexInput = 4,
        VertexShader = 8,
        TessellationControlShader = 16,
        TessellationEvaluationShader = 32,
        GeometryShader = 64,
        FragmentShader = 128,
        EarlyFragmentTests = 256,
        LateFragmentTests = 512,
        ColorAttachmentOutput = 1024,
        ComputeShader = 2048,
        Transfer = 4096,
        BottomOfPipe = 8192,
        Host = 16384,
        AllGraphics = 32768,
        AllCommands = 65536,
        None = 0,
        TransformFeedback = 0x01000000,
        ConditionalRendering = 0x00040000,
        AccelerationStructureBuild = 0x02000000,
        RayTracingShader = 0x00200000,
        ShadingRateImage = 0x00800000,
        TaskShader = 0x00080000,
        MeshShader = 0x00100000,
    };
}