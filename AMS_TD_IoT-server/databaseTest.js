const mongoose= require("mongoose");
mongoose.connect('mongodb+srv://atom2teamdirectory:lie9B21qlUKUEOoU@cluster0.4gzgb.mongodb.net/myFirstDatabase?retryWrites=true&w=majority')
const fs = require('fs')
const userSchema = new mongoose.Schema(
    {
      name: {
        type: String,
        required: true,
      },
  
      bio: {
        type: String,
      },
      title: {
        type: String,
      },
      username: {
        type: String,
        required: true,
        unique: true,
        trim: true,
        lowercase: true,
      },
      email: {
        type: String,
        required: true,
        unique: true,
        trim: true,
        lowercase: true,
      },
      collegeEmail: {
        type: String,
        trim: true,
        lowercase: true,
      },
      password: {
        type: String,
        trim: true,
      },
      defaultAvatar: {
        type: String,
      },
      avatar: {
        type: String,
      },
      dob: { type: Date },
      phone: { type: String },
      domain: {
        domainPrimary: {
          type: String,
        },
        domainSecondary: {
          type: String,
        },
        memberSince: {
          type: Date,
        },
      },
      roles: {
        type: Object,
      },
      college: {
        name: {
          type: String,
        },
        location: {
          type: String,
        },
        graduationYear: {
          type: Date,
        },
      },
      links: {
        instagram: {
          type: String,
        },
        github: {
          type: String,
        },
        linkedIn: {
          type: String,
        },
      },
      skillSet: {
        hard: [String],
        soft: [String],
      },
      interests: [String],
      stacks: [String],
      website: {
        type: String,
      },
      resume: {
        type: String,
      },
      status: {
        type: Boolean,
      },
    },
    {
      timestamps: true,
    }
  );

const student = mongoose.model('user',userSchema)
async function search(){
    try {
        const students = await student.find() 
        console.log(students);
    } catch (error) {
        console.log(error);
    }
}
search()