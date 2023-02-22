const mongoose = require('mongoose')
const sample_schema = new mongoose.Schema(
    {
        RFID:{
            type:String,
            default:'123456789'
        },
        REG_NO:{
            type:String,
            default:"RA2011031010032"
        }
    }
)
const smodel = mongoose.model('Student',sample_schema)
// async function createData(){
//     try {
//         const d = new smodel({
//             RFID:'1234567890'
//         })
//         await d.save()
//         return 1;
//     } catch (error) {
//         console.log(error);
//         return 0;
//     }
// }
// mongoose.connect("mongodb+srv://Riddhiman_Mongo:hello123@cluster1.b76yf.mongodb.net/MQTT?retryWrites=true&w=majority")
// createData()
module.exports = smodel
